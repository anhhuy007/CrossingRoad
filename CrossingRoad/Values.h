#pragma once

#include <windows.h>
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
	DIALOG = 5,
	BUTTON = 6,
	TEXT = 7,
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
	NORMAL,
	NUMBER, 
	COIN_NUMBER
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
	SMALL_TREE,
	BIG_TREE,
	ROCK,
	WATER,
	SMALL_LOG, 
	BIG_LOG,
	ITEM,
	COIN,
	PORTAL,
	GIFT, 
	DEER,
	SMALL_PINETREE,
	BIG_PINETREE,
	GRASS_LANE,
	ROAD_LANE,
	WATER_LANE,
	WINTER_LANE
};

enum class MapType {
	CLASSIC, 
	WINTER
};

enum class GameMode {
	ENDLESS_MODE,
	LEVEL_MODE
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

struct LaneInfo {
	LaneType laneType;
	int laneSpeed;
	MovingDirection objectDirection;
};

struct PlayerInfo {
	MovingDirection moveDirec;
	AnimationState aniState;
	int lanePos;
	COORD position;
};

struct GameMapInfo {
	MapType mapType;
	GameMode gameMode;
	std::vector<LaneInfo> lanesInfo;
	PlayerInfo playerInfo; // some  attributes are not used
	int level; // optional if game mode is LEVEL_MODE
	int score;
	int coin;
};