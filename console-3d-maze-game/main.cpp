/*
	Console 3D Maze Game
		© Amyr Ahmady (iAmir) - 2019
	File: main.cpp

	Repository: https://github.com/AmyrAhmady/Console-3D-Maze-Game
*/

#include <iostream>
#include "common.hpp"
#include "game.hpp"

int main()
{
	std::wstring mapPainting;
	mapPainting += L"================";
	mapPainting += L"|..............|";
	mapPainting += L"|.......=======|";
	mapPainting += L"|..............|";
	mapPainting += L"|..............|";
	mapPainting += L"|===...........|";
	mapPainting += L"|..............|";
	mapPainting += L"|..............|";
	mapPainting += L"|..............|";
	mapPainting += L"|......====..==|";
	mapPainting += L"|......|.......|";
	mapPainting += L"|......|.......|";
	mapPainting += L"|..............|";
	mapPainting += L"|......========|";
	mapPainting += L"|..............|";
	mapPainting += L"================";

	Size2D mapSize;
	mapSize.width = 16;
	mapSize.height = 16;

	Size2D screenSize;
	screenSize.width = 120;
	screenSize.height = 30;

	Game game(mapPainting, screenSize, mapSize);
	game.Play();
	return 0;
}