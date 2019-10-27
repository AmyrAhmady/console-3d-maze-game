/*
	Console 3D Maze Game
		© Amyr Ahmady (iAmir) - 2019
	File: buffer.cpp

	Repository: https://github.com/AmyrAhmady/Console-3D-Maze-Game
*/

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
#include <Windows.h>
#endif
#include <algorithm>
#include "common.hpp"
#include "game.hpp"
#include "console.hpp"

Console::Console(const Size2D &screenSize)
{
	this->screenSize = screenSize;

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
	outputBuffer = new CHAR_INFO[screenSize.width * screenSize.height];

	windowBuffer = { 0, 0, screenSize.width, screenSize.height };
	console = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
	SetConsoleActiveScreenBuffer(console);
	SetConsoleWindowInfo(console, true, &windowBuffer);
	std::cout << "\033]0;" << "Console 3D Maze Game" << "\007";
#else
	outputBuffer = new sOutput[screenSize.width * screenSize.height];
	std::cout << "\033]0;" << "Console 3D Maze Game" << "\007";
	std::cout << "\e[8;40;120t";
#endif
	
}

Console::~Console()
{
	delete outputBuffer;
	screenSize = {};
}

void Console::WriteOutput()
{
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
	WriteConsoleOutput(console, outputBuffer, { screenSize.width, screenSize.height }, { 0, 0 }, &windowBuffer);
#else
	std::string tempBuff;
	std::cout << "\033[0;0H";
	for (int i = 0; i < (screenSize.width * screenSize.height); i++)
		tempBuff.append(outputBuffer[i].color + outputBuffer[i].character);
	std::cout << tempBuff;
#endif
}

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)

void Console::SetChar(wchar_t character, unsigned short color, int index)
{
	outputBuffer[index].Char.UnicodeChar = character;
	outputBuffer[index].Attributes = color;
}

#else

void Console::SetChar(const std::string &character, const std::string &color, int index)
{
	outputBuffer[index].character = character;
	outputBuffer[index].color = color;
}

#endif