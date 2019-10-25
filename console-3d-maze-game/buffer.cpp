/*
	Console 3D Maze Game
		© Amyr Ahmady (iAmir) - 2019
	File: buffer.cpp

	Repository: https://github.com/AmyrAhmady/Console-3D-Maze-Game
*/

#include <Windows.h>
#include "common.hpp"
#include "game.hpp"
#include "buffer.hpp"

Buffer::Buffer(Game *phandle, size_t buffSize)
{
	outputBuffer = new CHAR_INFO[buffSize];
	gameHandle = phandle;
	screenSize = gameHandle->GetScreenSize();
}

Buffer::~Buffer()
{
	delete outputBuffer;
	screenSize = {};
}

void Buffer::WriteOutput()
{
	WriteConsoleOutput(gameHandle->consoleHandle, outputBuffer, { screenSize.width, screenSize.height }, { 0, 0 }, &gameHandle->windowBuffer);
}

void Buffer::WriteOutput(const CHAR_INFO* buffer)
{
	WriteConsoleOutput(gameHandle->consoleHandle, buffer, { screenSize.width, screenSize.height }, { 0, 0 }, &gameHandle->windowBuffer);
}

void Buffer::SetChar(wchar_t character, unsigned short attributes, int index)
{
	outputBuffer[index].Char.UnicodeChar = character;
	outputBuffer[index].Attributes = attributes;
}