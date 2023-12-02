#pragma once

// ----- my libs include -----
#include "CrossingRoad.h"
#include "GamePlayer.h"
#include "Lane.h"
#include "Log.h"
#include "Portal.h"
#include "Widget.h"
#include "MenuScreen.h"

// ----- standard libs include -----
#include <vector>
#include <string>

#define Image Graphic::Sprite

class GameMap : public CrossingRoad::GameScreen {
	// ---- game properties ----
	int level = 0;
	int collectedCoins = 0;
	int index = 0;
	int maxIndex = 0;
	float totalTime = 0.0f;
	bool endlessMode = false;
	bool isFirstHit = false;
	bool isFirstOnLog = false;

	GamePlayer* player = nullptr;
	Image grid;
	Widget::Dialog pausegame_dialog;
	Widget::Dialog gameover_dialog;

protected:
	int score = 0;
	std::vector<Lane*> lanes;
	Portal portal;
		
	Graphic::Sprite grasslane;
	Graphic::Sprite snowlane;
	Graphic::Sprite waterlane;
	Graphic::Sprite roadlane;
	Graphic::Sprite roadMarking;
public: 
	GameMap(CrossingRoad* game) : GameScreen(game) {};

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
