#pragma once

#ifndef VALUES_H
#define VALUES_H

#include <windows.h>
#include <map>
#include <string>
#include "Graphic.h"

const float FPS = 60;
const int keyNumber = 256;
const int characterSize = 16;
const COORD FIRSTBLOCK = { 66, -103 }; 
const int MAXBLOCK = 16;
const int MAXLANE = 16;
const int LETTER_SPACE = 2;

enum GameScreenLimit : int {
	LEFT = 0,
	TOP = 0,
	RIGHT = 460,
	BOTTOM = 240
};

enum class AnimationState {
	NORMAL = 0,
	TURN_LEFT = 1,
	TURN_RIGHT = 2, 
	TURN_BACK = 3,
	DEAD = 4,
	DROWN = 5
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
	BACKGROUND = 0,
	LAND = 1,
	DECORATOR = 2,
	LOG = 3,
	OBSTACLE = 4,
	VEHICLE = 4, 
	PLAYER = 4,
	TEXT = 5
};

enum class VehicleType {
	CAR = 1,
	TRUCK = 2
};

enum class LogType {
	SMALL_LOG,
	BIG_LOG
};

enum class TreeType {
	SMALL_TREE,
	BIG_TREE
};

enum class LaneType {
	GRASS,
	WATER,
	ROAD
};

enum class Player {
	CHICK,
	DUCKY,
	DOGGO,
	MEOW, 
	DINO
};

enum class TextFont {
	TITLE,
	NORMAL
};

enum class ButtonState {
	NORMAL,
	ON_HOVER,
	ON_TRIGGER
};

enum ObjectCollis : int {
	NORMAL_LANE = 0,
	VEHICLE_COLLIS = 1,
	TREE = 2,
	BUSH = 2, 
	ROCK = 2,
	WATER = 3, 
	FLOATING_LOG = 4
};

enum class ObjectType {
	PLAYER,
	CAR,
	TRUCK,
	TREE_1, // small tree
	TREE_2, // big tree
	ROCK,
	WATER,
	FLOATING_OBJECT_1, // small log
	FLOATING_OBJECT_2, // big log
	ITEM,
	COIN,
	PORTAL
};

enum class MapType {
	CLASSIC, 
	WINTER
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

struct AnimationSprite {
	Graphic::Sprite sprite;
	AnimationState state;

	AnimationSprite(Graphic::Sprite _sprite, AnimationState _state) {
		sprite = _sprite;
		state = _state;
	}
};

struct GameInformation {
	int level;
	int score;
	int collectedCoins;
	float totalTime;
	bool endlessMode;
};

#endif // !VALUES_H
