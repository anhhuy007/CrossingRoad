#pragma once

#ifndef GAMEMAP_H
#define GAMEMAP_H

// ----- my libs include -----
#include "CrossingRoad.h"
#include "GamePlayer.h"
#include "Lane.h"
#include "Log.h"

// ----- standard libs include -----
#include <vector>
#include <string>

class GameMap : public CrossingRoad::GameScreen {

protected: 
	int level = 0;
	int score = 0;
	int collectedCoins = 0;
	int playerIndex = 0;
	float totalTime = 0.0f;
	std::vector<Lane*> lanes;
	
	GamePlayer* player = nullptr;
	Graphic::Sprite grid;

public: 
	GameMap(CrossingRoad* game) : GameScreen(game) {};

	// overrided functions 
	bool OnCreate();
	bool OnUpdate(float elapsedTime);
	bool OnDestroy() { return false; };

	// must override functions
	virtual void CreateLanes() = 0;
	virtual void SetScreenColor() = 0;
	virtual void ScrollUp() = 0;

	// methods
	void Render();
	void HandlePlayerCollision(float elapsedTime);
	Log GetLogByLaneId(int laneId);
};


#endif // !GAMEMAP_H
