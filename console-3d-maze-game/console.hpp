/*
	Console 3D Maze Game
		© Amyr Ahmady (iAmir) - 2019
	File: buffer.hpp

	Repository: https://github.com/AmyrAhmady/Console-3D-Maze-Game
*/

#pragma once

class Console
{
public:
	Console(const Size2D &screenSize);
	~Console();

	void WriteOutput(const CHAR_INFO* buffer);
	void WriteOutput();
	void SetChar(wchar_t character, unsigned short attributes, int index);

	CHAR_INFO *Get() { return outputBuffer; }

private:
	CHAR_INFO *outputBuffer;
	Size2D screenSize;
	HANDLE console;
	SMALL_RECT windowBuffer;
};
