/*
	Console 3D Maze Game
		© Amyr Ahmady (iAmir) - 2019
	File: linux_keyboard.cpp

	Repository: https://github.com/AmyrAhmady/Console-3D-Maze-Game
*/

#if !(defined(WIN32) || defined(_WIN32))

#include <unordered_map>
#include "linux_keyboard.hpp"
#include "common.hpp"

std::unordered_map<short, short> KeysMap;

Keyboard::Keyboard() 
{
	active = true;
	keyboard_fd = 0;
	keyboard_ev = new input_event();
	keyboard_fd = open(KEYBOARD_DEV, O_RDONLY | O_NONBLOCK);
	if (keyboard_fd > 0) 
	{
		ioctl(keyboard_fd, EVIOCGNAME(256), name);
		active = true;
		thread = std::thread(Keyboard::loop, this);
		thread.detach();
	}
}

Keyboard::~Keyboard() 
{
	if (keyboard_fd > 0) 
	{
		active = false;
		close(keyboard_fd);
	}
	delete keyboard_ev;
	keyboard_fd = 0;
}

void* Keyboard::loop(void *obj) 
{
	while (reinterpret_cast<Keyboard *>(obj)->active) 
		reinterpret_cast<Keyboard *>(obj)->readEv();
}

void Keyboard::readEv() 
{
	int bytes = read(keyboard_fd, keyboard_ev, sizeof(*keyboard_ev));
	if (bytes > 0) 
	{
		if (keyboard_ev->type & EV_KEY)
			KeysMap[keyboard_ev->code] = keyboard_ev->value;		
	}
}

short Keyboard::linuxIsKeyDown(char key)
{
	return (KeysMap[key] == 1 || KeysMap[key] == 2);
}

#endif