#pragma once

#ifndef GAMEMAP_H
#define GAMEMAP_H

// ----- my libs include -----
#include "CrossingRoad.h"
#include "GamePlayer.h"
#include "Lane.h"

// ----- standard libs include -----
#include <vector>
#include <string>

class GameMap : public CrossingRoad::GameState {

protected: 
	int level;
	int score;
	int collectedCoins;
	int playerIndex;
	float totalTime;
	vector<Lane*> lanes;
	
	GamePlayer* player;

public: 
	GameMap();
	GameMap(CrossingRoad* game);

	virtual bool Create();
	virtual void CreateLanes() = 0;
	virtual bool Update(float elapsedTime);
	virtual void Render();
};


#endif // !GAMEMAP_H
