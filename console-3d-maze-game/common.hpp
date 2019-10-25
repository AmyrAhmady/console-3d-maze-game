/*
	Console 3D Maze Game
		© Amyr Ahmady (iAmir) - 2019
	File: common.hpp

	Repository: https://github.com/AmyrAhmady/Console-3D-Maze-Game
*/

#pragma once
#include <Windows.h>

struct Vector2
{
	float fX;
	float fY;
};

struct CamInfo
{
	float fFOV;
	float fDepth;
};

struct Size2D
{
	short width;
	short height;
};

struct IntPair
{
	int a;
	int b;
};

enum MOVE_TYPE
{
	MOVE_BACKWARD,
	MOVE_FROWARD
};

enum TURNING_TYPE
{
	TURN_LEFT,
	TURN_RIGHT
};

namespace utils
{
	inline unsigned short IsKeyDown(char key)
	{
		return GetAsyncKeyState(static_cast<unsigned short>(key)) & 0x8000;
	}
}