#pragma once

// ----- my libs include -----
#include "CrossingRoad.h"
#include "GamePlayer.h"
#include "Lane.h"
#include "Log.h"
#include "Portal.h"
#include "Widget.h"
#include "MenuScreen.h"
#include "FileIO.h"

// ----- standard libs include -----
#include <vector>
#include <string>

#define Image Graphic::Sprite

class GameMap : public CrossingRoad::GameScreen {
	// ---- game properties ----
	int maxIndex = 0;
	float totalTime = 0.0f;
	bool endlessMode = false;
	bool isFirstHit = false;
	bool isFirstOnLog = false;

	GamePlayer* player = nullptr;
	Image grid;
	Widget::Dialog pausegame_dialog;
	Widget::Dialog gameover_dialog;
	Widget::Text level;

protected:
	GameMapInfo gameInfo; // manage game information
	std::vector<Lane*> lanes;
	Portal portal;
		
	Graphic::Sprite grasslane;
	Graphic::Sprite snowlane;
	Graphic::Sprite waterlane;
	Graphic::Sprite roadlane;
	Graphic::Sprite railwaylane;
	Graphic::Sprite roadMarking;
public: 
	GameMap(CrossingRoad* game) : GameScreen(game) {};
	GameMap(CrossingRoad* game, GameMapInfo gameInfo) : GameScreen(game), gameInfo(gameInfo) {};

	void CreateNewGame();
	void LoadSavedGame();
	void InitWidget();

	void GetNewEndlessGame();
	void GetNewGameLevel(int level);
	void LoadSavedLanes();

	std::string GetSavedGameName();
	void SaveGame();

	GameMapInfo GetGameMapInfo(
		GameMapInfo partialInfo,
		GamePlayer* player,
		std::vector<Lane*> lanes
	);

	// overrided functions 
	bool OnCreate();
	bool OnUpdate(float elapsedTime);
	bool OnPause();
	bool OnDestroy() { return false; };

	// must override functions
	virtual void CreateLanes() = 0;
	virtual void SetScreenColor() = 0;
	virtual void ScrollUp() = 0;

	// methods
	void Render();
	bool HandlePlayerCollision(float elapsedTime);
	Log GetLogByLaneId(int laneId);
};
