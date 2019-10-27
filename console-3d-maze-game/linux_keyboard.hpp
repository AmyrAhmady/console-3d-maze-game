/*
	Console 3D Maze Game
		© Amyr Ahmady (iAmir) - 2019
	File: linux_keyboard.hpp

	Repository: https://github.com/AmyrAhmady/Console-3D-Maze-Game
*/

#pragma once

#if !(defined(WIN32) || defined(_WIN32))

#include <iostream>
#include <fcntl.h>
#include <unistd.h>
#include <thread>
#include <linux/input.h>

#define KEYBOARD_DEV "/dev/input/event1"

class Keyboard 
{
private:
	std::thread thread;
	bool active;
	int keyboard_fd;
	input_event *keyboard_ev;
	char name[256];

public:
	Keyboard();
	~Keyboard();
	static void* loop(void* obj);
	void readEv();
	short linuxIsKeyDown(char key);
};


#endif