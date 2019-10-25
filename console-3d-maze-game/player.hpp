/*
	Console 3D Maze Game
		© Amyr Ahmady (iAmir) - 2019
	File: player.hpp

	Repository: https://github.com/AmyrAhmady/Console-3D-Maze-Game
*/

#pragma once

class Player
{
public:
	float speed;
	float stepSize;
	float camDepth;
	float camFOV;

	Player(Game *handle);
	~Player();

	void Move(MOVE_TYPE moveType, float delay);
	void Turn(TURNING_TYPE turnType, float delay);
	std::pair<float, bool> GetCollideStatus(int x);

	void SetAngle(float value) { angle = value; }
	float GetAngle() { return angle; }
	void SetPosition(const Vector2 &pos) { position = { pos.fX, pos.fY }; }
	Vector2 GetPosition() { return position; }

private:
	float GetRayDirection(float xCoord);
	std::pair<int, int> SendRayCast(const Vector2 &direction);

	Game *gameHandle;
	Vector2 position = { 0.0f, 0.0f };
	float angle = 0.0;
};