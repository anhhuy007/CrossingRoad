#pragma once

#ifndef VALUES_H
#define VALUES_H

#include <windows.h>

const int keyNumber = 256;
const int characterSize = 16;

enum GameScreenLimit : int {
	LEFT = 0,
	TOP = 0,
	RIGHT = 460,
	BOTTOM = 240
};

enum class AnimationState {
	NORMAL = 0,
	JUMP = 1,
	TURN_LEFT = 2,
	TURN_RIGHT = 3, 
	TURN_BACK = 4,
	DIED = 5
};

enum class MovingDirection {
	NONE = 0,
	UP = 1,
	DOWN = 2,
	LEFT = 3,
	RIGHT = 4
};

enum Keyboard : int {
	UP_KEY = VK_UP,
	DOWN_KEY = VK_DOWN,
	LEFT_KEY = VK_LEFT,
	RIGHT_KEY = VK_RIGHT,
	SPACE_KEY = VK_SPACE,
	ENTER_KEY = VK_RETURN,
	ESCAPE_KEY = VK_ESCAPE,
};

enum class PlayerState {
	STATE_ALIVE,
	STATE_DEAD
};

enum Overlapped : int {
	LAND = 1,
	OBSTACLE = 2,
	VEHICLE = 3, 
	PLAYER = 10000
};

enum VehicleType {
	CAR = 1,
	TRUCK = 2
};

struct GameSpeed {
	int X_HORIZONTAL = 0;
	int Y_HORIZONTAL = 0;
	int X_VERTICAL = 0;
	int Y_VERTICAL = 0;

	GameSpeed() {
		X_HORIZONTAL = 0;
		Y_HORIZONTAL = 0;
		X_VERTICAL = 0;
		Y_VERTICAL = 0;
	}

	GameSpeed(int xh, int yh, int xv, int yv) {
		X_HORIZONTAL = xh;
		Y_HORIZONTAL = yh;
		X_VERTICAL = xv;
		Y_VERTICAL = yv;
	}
};

enum class TreeType {
	SMALL_TREE,
	BIG_TREE
};

#endif // !VALUES_H
