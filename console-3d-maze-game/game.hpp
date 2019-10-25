/*
	Console 3D Maze Game
		© Amyr Ahmady (iAmir) - 2019
	File: game.hpp

	Repository: https://github.com/AmyrAhmady/Console-3D-Maze-Game
*/

#pragma once
#include <iostream>

class Buffer;
class Player;

class Game
{
public:
	SMALL_RECT windowBuffer;
	HANDLE consoleHandle;

	Game();
	Game(const std::wstring &map, const Size2D &screenSize, const Size2D &radarSize);
	~Game();

	void Play();
	wchar_t GetMapChar(int index);
	Size2D GetScreenSize() { return screenSize; }
	Size2D GetMapSize() { return mapSize; }

private:
	std::wstring mapPainting;
	Size2D mapSize;
	Size2D screenSize;
	Buffer *output;
	Player *player;

	short GetWallShade(float distance);
	short GetFloorShade(int y);
	void DrawRadar(const Vector2 &playerPos);
};