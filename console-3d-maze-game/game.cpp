/*
	Console 3D Maze Game
		© Amyr Ahmady (iAmir) - 2019
	File: game.cpp

	Repository: https://github.com/AmyrAhmady/Console-3D-Maze-Game
*/

#include <iostream>
#include <chrono>
#include <memory>
#include <algorithm>
#include <vector>
#include <cmath>
#include "common.hpp"
#include "game.hpp"
#include "console.hpp"
#include "player.hpp"
#include "color.hpp"

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
#define IsKeyDown(x) utils::win32IsKeyDown(x)
#else
#include "linux_keyboard.hpp"
#define IsKeyDown(x) keyboard->linuxIsKeyDown(x)
#endif

Game::Game()
{
	short screenWidth = 120;
	short screenHeight = 40;

	this->mapSize = { 16, 16 };
	this->screenSize = { screenWidth, screenHeight };

	mapPainting = L"";
	mapPainting += L"================";
	mapPainting += L"|..............|";
	mapPainting += L"|.......=======|";
	mapPainting += L"|..............|";
	mapPainting += L"|..............|";
	mapPainting += L"|===...........|";
	mapPainting += L"|..............|";
	mapPainting += L"|..............|";
	mapPainting += L"|..............|";
	mapPainting += L"|......====..==|";
	mapPainting += L"|......|.......|";
	mapPainting += L"|......|.......|";
	mapPainting += L"|..............|";
	mapPainting += L"|......========|";
	mapPainting += L"|..............|";
	mapPainting += L"================";

	player = std::unique_ptr<Player>(new Player());
	this->output = std::unique_ptr<Console>(new Console({ screenWidth, screenHeight }));
}

Game::Game(const std::wstring &map, const Size2D &screenSize, const Size2D &radarSize)
{
	this->mapSize = radarSize;
	this->screenSize = screenSize;
	mapPainting = map;

	player = std::unique_ptr<Player>(new Player());
	this->output = std::unique_ptr<Console>(new Console(screenSize));
}

Game::~Game()
{

}

void Game::Play()
{
#if !(defined(WIN32) || defined(_WIN32))
	std::unique_ptr<Keyboard> keyboard = std::unique_ptr<Keyboard>(new Keyboard());
#endif
	auto timeTick1 = std::chrono::system_clock::now();

	while (1)
	{
		Vector2 PlayerPos = player->GetPosition();
		float PlayerAngle = player->GetAngle();
		auto timeTick2 = std::chrono::system_clock::now();
		std::chrono::duration<float> diffTime = timeTick2 - timeTick1;
		timeTick1 = timeTick2;
		float elapsedTime = diffTime.count();

		if (IsKeyDown(KEY_A))
			player->Turn(TURN_LEFT, elapsedTime);

		if (IsKeyDown(KEY_D))
			player->Turn(TURN_RIGHT, elapsedTime);

		if (IsKeyDown(KEY_W))
		{
			player->Move(MOVE_FROWARD, elapsedTime);
			Vector2 pos = player->GetPosition();
			if (GetMapChar(static_cast<int>(pos.fX) * mapSize.width + static_cast<int>(pos.fY)) == '=' ||
				GetMapChar(static_cast<int>(pos.fX) * mapSize.width + static_cast<int>(pos.fY)) == '|')
				player->Move(MOVE_BACKWARD, elapsedTime);

		}

		if (IsKeyDown(KEY_S))
		{
			player->Move(MOVE_BACKWARD, elapsedTime);
			Vector2 pos = player->GetPosition();
			if (GetMapChar(static_cast<int>(pos.fX) * mapSize.width + static_cast<int>(pos.fY)) == '=' ||
				GetMapChar(static_cast<int>(pos.fX) * mapSize.width + static_cast<int>(pos.fY)) == '|')
				player->Move(MOVE_FROWARD, elapsedTime);
		}

		for (int x = 0; x < screenSize.width; x++)
		{
			std::pair<float, bool> collideData = GetCollideStatus(x);
			float wallDistance = collideData.first;
			bool isBoundary = collideData.second;

			int wallHeight = static_cast<int>((static_cast<float>(screenSize.height) / 2.0) - static_cast<float>(screenSize.height) / wallDistance);
			int floorDrawHeight = screenSize.height - wallHeight;

			short currentShade = GetWallShade(wallDistance);
			if (isBoundary)
				currentShade = ' ';

			for (int y = 0; y < screenSize.height; y++)
			{
				if (y <= wallHeight)
					output->SetChar(' ', color::Blank, y*screenSize.width + x);
				else if (y > wallHeight && y <= floorDrawHeight)
				{
					output->SetChar(currentShade, color::bgBlackTextRed, y*screenSize.width + x);
				}	
				else
				{
					currentShade = GetFloorShade(y);
					output->SetChar(currentShade, color::bgBlackTextGreen, y*screenSize.width + x);
				}
			}
		}

		DrawRadar(PlayerPos);

		output->SetChar('\0', color::Black, screenSize.width * screenSize.height - 1);
		output->WriteOutput();

	}
}

float Game::GetRayDirection(float xCoord)
{
	return (player->GetAngle() - player->camFOV / 2.0f) + (xCoord / static_cast<float>(screenSize.width)) * player->camFOV;
}

std::pair<int, int> Game::SendRayCast(const Vector2 &direction)
{
	Vector2 position = player->GetPosition();
	std::pair<int, int> tempVar = {
		static_cast<int>(position.fX + direction.fX),
		static_cast<int>(position.fY + direction.fY)
	};
	return tempVar;
}

std::pair<float, bool> Game::GetCollideStatus(int x)
{
	Vector2 position = player->GetPosition();
	float rayAngle = GetRayDirection(static_cast<float>(x));
	float wallDistance = 0.0f;
	bool isBoundary = false;
	bool isHittingWall = false;
	float fEyeX = sinf(rayAngle);
	float fEyeY = cosf(rayAngle);

	while (!isHittingWall && wallDistance < player->camDepth)
	{
		wallDistance += player->stepSize;
		std::pair<int, int> rayTest = SendRayCast({ fEyeX * wallDistance, fEyeY * wallDistance });

		if (rayTest.first < 0 || rayTest.first >= mapSize.width || rayTest.second < 0 || rayTest.second >= mapSize.height)
		{
			isHittingWall = true;
			wallDistance = player->stepSize;
		}
		else
		{
			if (GetMapChar(rayTest.first * mapSize.width + rayTest.second) == '=' ||
				GetMapChar(rayTest.first * mapSize.width + rayTest.second) == '|')
			{
				isHittingWall = true;

				std::vector<std::pair<float, float>> p;

				for (int tx = 0; tx < 2; tx++)
					for (int ty = 0; ty < 2; ty++)
					{
						float vy = static_cast<float>(rayTest.second) + ty - position.fY;
						float vx = static_cast<float>(rayTest.first) + tx - position.fX;
						float d = sqrt(vx*vx + vy * vy);
						float dot = (fEyeX * vx / d) + (fEyeY * vy / d);
						p.push_back(std::make_pair(d, dot));
					}

				std::sort(p.begin(), p.end(),
					[](const std::pair<float, float> &left, const std::pair<float, float> &right)
				{
					return left.first < right.first;
				}
				);

				float boundVal = 0.01f;
				if (acos(p.at(0).second) < boundVal) isBoundary = true;
				if (acos(p.at(1).second) < boundVal) isBoundary = true;
				if (acos(p.at(2).second) < boundVal) isBoundary = true;
			}
		}
	}

	return { wallDistance, isBoundary };
}

wchar_t Game::GetMapChar(int index)
{
	return mapPainting.c_str()[index];
}

short Game::GetWallShade(float distance)
{
	short wallShade = ' ';
	if (distance <= player->camDepth / 4.0f)			wallShade = 0x2588;
	else if (distance < player->camDepth / 3.0f)		wallShade = 0x2593;
	else if (distance < player->camDepth / 2.0f)		wallShade = 0x2592;
	else if (distance < player->camDepth)				wallShade = 0x2591;
	else												wallShade = ' ';
	return wallShade;
}

short Game::GetFloorShade(int y)
{
	short currentShade = ' ';
	float distance = 1.0f - (((float)y - screenSize.height / 2.0f) / ((float)screenSize.height / 2.0f));
	if (distance < 0.25)		currentShade = '#';
	else if (distance < 0.5)	currentShade = 'x';
	else if (distance < 0.75)	currentShade = '.';
	else if (distance < 0.9)	currentShade = '-';
	else				currentShade = ' ';
	return currentShade;
}

void Game::DrawRadar(const Vector2 &playerPos)
{
	for (int nx = 0; nx < mapSize.width; nx++)
	{
		for (int ny = 0; ny < mapSize.height; ny++)
		{
			output->SetChar(mapPainting[ny * mapSize.width + nx], color::bgBlueTextYellow, ny * screenSize.width + nx);
		}
	}
	output->SetChar('O', color::bgBlackTextRed, static_cast<int>(playerPos.fX) * screenSize.width + static_cast<int>(playerPos.fY));
}