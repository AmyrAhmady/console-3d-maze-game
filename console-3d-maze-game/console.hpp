/*
	Console 3D Maze Game
		© Amyr Ahmady (iAmir) - 2019
	File: buffer.hpp

	Repository: https://github.com/AmyrAhmady/Console-3D-Maze-Game
*/

#pragma once
#if !(defined(WIN32) || defined(_WIN32))
#include <codecvt>
#include <locale>
#endif

class Console
{
	struct sOutput
	{
		wchar_t character;
		std::string color;
	};

public:
	Console(const Size2D &screenSize);
	~Console();

	void WriteOutput();

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
	void SetChar(wchar_t character, unsigned short color, int index);
#else 
	void SetChar(wchar_t character, const std::string &color, int index);
#endif

private:
	Size2D screenSize;

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
	HANDLE console;
	SMALL_RECT windowBuffer;
	CHAR_INFO *outputBuffer;
#else 
	sOutput *outputBuffer;
	std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>, wchar_t> convert;
#endif
};