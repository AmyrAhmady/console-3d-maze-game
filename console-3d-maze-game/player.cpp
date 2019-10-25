/*
	Console 3D Maze Game
		© Amyr Ahmady (iAmir) - 2019
	File: player.cpp

	Repository: https://github.com/AmyrAhmady/Console-3D-Maze-Game
*/

#include <math.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include "common.hpp"
#include "game.hpp"
#include "player.hpp"

Player::Player(Game *handle)
{
	gameHandle = handle;
	camFOV = 3.24159f / 4.0f;
	camDepth = 16.0f;
	speed = 5.0f;
	stepSize = 0.1f;
	position.fX = 14.7f;
	position.fY = 3.09f;
	angle = 0.0f;
}

Player::~Player()
{

}

void Player::Move(MOVE_TYPE moveType, float delay)
{
	if (moveType == MOVE_FROWARD)
	{
		position.fX += sinf(angle) * speed * delay;
		position.fY += cosf(angle) * speed * delay;
	}
	else if (moveType == MOVE_BACKWARD)
	{
		position.fX -= sinf(angle) * speed * delay;
		position.fY -= cosf(angle) * speed * delay;
	}
}

void Player::Turn(TURNING_TYPE turnType, float delay)
{
	if (turnType == TURN_LEFT)
		angle -= (speed * 0.75f) * delay;
	else if (turnType == TURN_RIGHT)
		angle += (speed * 0.75f) * delay;
}

float Player::GetRayDirection(float xCoord)
{
	return (angle - camFOV / 2.0f) + (xCoord / static_cast<float>(gameHandle->GetScreenSize().width)) * camFOV;
}

std::pair<int, int> Player::SendRayCast(const Vector2 &direction)
{
	std::pair<int, int> tempVar = {
		static_cast<int>(position.fX + direction.fX),
		static_cast<int>(position.fY + direction.fY)
	};
	return tempVar;
}

std::pair<float, bool> Player::GetCollideStatus(int x)
{
	Size2D mapSize = gameHandle->GetMapSize();

	float rayAngle = GetRayDirection(static_cast<float>(x));
	float wallDistance = 0.0f;
	bool isBoundary = false;
	bool isHittingWall = false;
	float fEyeX = sinf(rayAngle);
	float fEyeY = cosf(rayAngle);

	while (!isHittingWall && wallDistance < camDepth)
	{
		wallDistance += stepSize;
		std::pair<int, int> rayTest = SendRayCast({ fEyeX * wallDistance, fEyeY * wallDistance });

		if (rayTest.first < 0 || rayTest.first >= mapSize.width || rayTest.second < 0 || rayTest.second >= mapSize.height)
		{
			isHittingWall = true;
			wallDistance = stepSize;
		}
		else
		{
			if (gameHandle->GetMapChar(rayTest.first * mapSize.width + rayTest.second) == '=' ||
				gameHandle->GetMapChar(rayTest.first * mapSize.width + rayTest.second) == '|')
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

				float boundVal = 0.01;
				if (acos(p.at(0).second) < boundVal) isBoundary = true;
				if (acos(p.at(1).second) < boundVal) isBoundary = true;
				if (acos(p.at(2).second) < boundVal) isBoundary = true;
			}
		}
	}

	return { wallDistance, isBoundary };
}