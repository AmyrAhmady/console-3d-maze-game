/*
	Console 3D Maze Game
		© Amyr Ahmady (iAmir) - 2019
	File: player.cpp

	Repository: https://github.com/AmyrAhmady/Console-3D-Maze-Game
*/

#include <cmath>
#include <iostream>
#include "common.hpp"
#include "game.hpp"
#include "player.hpp"

Player::Player()
{
	camFOV = 3.24159f / 4.0f;
	camDepth = 16.0f;
	speed = 5.0f;
	stepSize = 0.1f;
	position.fX = 14.7f;
	position.fY = 3.09f;
	angle = 0.0f;
}

Player::~Player()
{

}

void Player::Move(MOVE_TYPE moveType, float delay)
{
	if (moveType == MOVE_FROWARD)
	{
		position.fX += sinf(angle) * speed * delay;
		position.fY += cosf(angle) * speed * delay;
	}
	else if (moveType == MOVE_BACKWARD)
	{
		position.fX -= sinf(angle) * speed * delay;
		position.fY -= cosf(angle) * speed * delay;
	}
}

void Player::Turn(TURNING_TYPE turnType, float delay)
{
	if (turnType == TURN_LEFT)
		angle -= (speed * 0.75f) * delay;
	else if (turnType == TURN_RIGHT)
		angle += (speed * 0.75f) * delay;
}