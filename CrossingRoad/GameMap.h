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
	Graphic::Sprite grid;

public: 
	GameMap();
	GameMap(CrossingRoad* game);

	virtual bool Create();
	virtual void CreateLanes() = 0;
	bool Update(float elapsedTime);
	void Render();
};


#endif // !GAMEMAP_H
