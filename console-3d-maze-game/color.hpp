/*
	Console 3D Maze Game
		© Amyr Ahmady (iAmir) - 2019
	File: color.hpp

	Repository: https://github.com/AmyrAhmady/Console-3D-Maze-Game
*/

#pragma once
#include <string>

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)

namespace color
{
	constexpr char Black = 0;
	constexpr char Red = 4;
	constexpr char Green = 2;
	constexpr char bgBlueTextYellow  = 22;
	constexpr char bgBlackTextRed = 12;
}

#else 

namespace color
{
	const std::string Black = "\x1b[30m";
	const std::string Red = "\x1b[31m";
	const std::string Green = "\x1b[32m";
	const std::string Yellow = "\x1b[33m";

	namespace background
	{
		const std::string Black = "\x1b[40m";
		const std::string Blue = "\x1b[44m";
	}

	const std::string bgBlueTextYellow = Yellow + background::Blue;
	const std::string bgBlackTextRed = Red + background::Black;
}


#endif