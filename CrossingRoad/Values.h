#pragma once

#include <windows.h>
#include <string>
#include "Graphic.h"

#include "Sound.h"

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
	BACKSPACE_KEY = VK_BACK,
	DELETE_KEY = VK_DELETE,
	A_KEY = 65,
	Z_KEY = 90,
	a_KEY = 97,
	z_KEY = 122,
	NUM_0_KEY = 48,
	NUM_9_KEY = 57
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
	TRAFFIC_LIGHT = 4,
	DIALOG = 6,
	BUTTON = 7,
	TEXT = 8,
};

enum class VehicleType {
	CAR = 1,
	TRUCK = 2,
	TRAIN = 3
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
	ROAD,
	SNOW,
	RAILWAY
};

enum class Player {
	DUCKY,
	CHICK,
	FROSTY,
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
	NONE, 
	PLAYER,
	RED_CAR,
	GREEN_CAR,
	RED_TRUCK,
	TRAIN,
	SMALL_TREE,
	BIG_TREE,
	ROCK,
	SNOW_ROCK,
	WATER,
	SMALL_LOG, 
	BIG_LOG,
	ITEM,
	COIN,
	PORTAL,
	GIFT, 
	DEER,
	SNOWMAN, 
	SMALL_PINETREE,
	BIG_PINETREE,
	GRASS_LANE,
	ROAD_LANE,
	WATER_LANE,
	RAILWAY_LANE,
	SNOW_LANE, 
	TEXT_WIDGET,
	BUTTON_WIDGET
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

struct ObjectInfo {
	ObjectType objType;
	float speed;
	COORD position;
};

struct PortalInfo {
	short visible;
	int lanePos;
	COORD position;

	PortalInfo() {
		visible = 0;
		lanePos = 0;
		position = { 0, 0 };
	}

	PortalInfo(
		short _visible,
		int _lanePos,
		COORD _position
	) {
		visible = _visible;
		lanePos = _lanePos;
		position = _position;
	}

	PortalInfo(const PortalInfo& other) {
		visible = other.visible;
		lanePos = other.lanePos;
		position = other.position;
	}
};

struct LaneInfo {
	int lanePos;
	LaneType laneType;
	MovingDirection objectDirection;
	std::vector<ObjectInfo> objectsInfo;

	LaneInfo() {
		lanePos = 0;
		laneType = LaneType::GRASS;
		objectDirection = MovingDirection::NONE;
	}

	LaneInfo(const LaneInfo& other) {
		lanePos = other.lanePos;
		laneType = other.laneType;
		objectDirection = other.objectDirection;
		objectsInfo.clear();
		for (auto obj : other.objectsInfo) {
			objectsInfo.push_back(obj);
		}
	}
};

struct PlayerInfo {
	char playerName[20];
	Player playerType;
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
	PortalInfo portalInfo;
	int endLane; // portal position in lane
	int level; // optional if game mode is LEVEL_MODE
	int score;
	int coin;

	GameMapInfo() {
		mapType = MapType::CLASSIC;
		gameMode = GameMode::ENDLESS_MODE;
		endLane = 0;
		level = 0;
		score = 0;
		coin = 0;
	}

	GameMapInfo(const GameMapInfo& other) {
		mapType = other.mapType;
		gameMode = other.gameMode;
		lanesInfo.clear();
		for (auto lane : other.lanesInfo) {
			lanesInfo.push_back(lane);
		}
		playerInfo = other.playerInfo;
		portalInfo = other.portalInfo;
		endLane = other.endLane;
		level = other.level;
		score = other.score;
		coin = other.coin;
	}
};

struct SavedGameDisplayInfo {
	int index;
	std::string playerName;
	std::string fileName;
	GameMode gameMode;
	int score;

	SavedGameDisplayInfo() {
		index = 0;
		playerName = "";
		fileName = "";
		gameMode = GameMode::ENDLESS_MODE;
		score = 0;
	}

	SavedGameDisplayInfo(
		int _index,
		std::string _playerName,
		std::string _fileName,
		GameMode _gameMode,
		int _score
	) {
		index = _index;
		playerName = _playerName;
		fileName = _fileName;
		gameMode = _gameMode;
		score = _score;
	}
};

struct LeaderBoardInfo {
	std::string playername;
	int score;
	int level;
	GameMode gameMode;

	LeaderBoardInfo() {
		playername = "";
		score = 0;
		level = 0;
		gameMode = GameMode::ENDLESS_MODE;
	}

	LeaderBoardInfo(
		std::string _playername,
		int _score,
		int _level,
		GameMode _gameMode
	) {
		playername = _playername;
		score = _score;
		level = _level;
		gameMode = _gameMode;
	}
};


struct PlayerOption {

	Sound *sound;
	Player player;
	PlayerOption() {
		player = Player::CHICK;
		sound = sound->getInstance();
	}
};
