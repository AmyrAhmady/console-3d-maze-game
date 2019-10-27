/*
	Console 3D Maze Game
		© Amyr Ahmady (iAmir) - 2019
	File: buffer.hpp

	Repository: https://github.com/AmyrAhmady/Console-3D-Maze-Game
*/

#pragma once

class Console
{
	struct sOutput
	{
		std::string character;
		std::string color;
	};

public:
	Console(const Size2D &screenSize);
	~Console();

	void WriteOutput();

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
	void SetChar(wchar_t character, unsigned short color, int index);
#else 
	void SetChar(const std::string &character, const std::string &color, int index);
#endif

private:
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
	CHAR_INFO *outputBuffer;
#else 
	sOutput *outputBuffer;
#endif
	Size2D screenSize;
	HANDLE console;
	SMALL_RECT windowBuffer;
};
