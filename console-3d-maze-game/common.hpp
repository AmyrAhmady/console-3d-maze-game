/*
	Console 3D Maze Game
		© Amyr Ahmady (iAmir) - 2019
	File: common.hpp

	Repository: https://github.com/AmyrAhmady/Console-3D-Maze-Game
*/

#pragma once
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
#include <Windows.h>

#define KEY_A 'A'
#define KEY_S 'S'
#define KEY_D 'D'
#define KEY_W 'W'

#else

#define KEY_A 30
#define KEY_S 31
#define KEY_D 32
#define KEY_W 17

#endif

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
	inline unsigned short win32IsKeyDown(char key)
	{
		#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
			return GetAsyncKeyState(static_cast<unsigned short>(key)) & 0x8000;
		#else
			return 0;
		#endif
	}
}