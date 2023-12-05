#pragma once

#include "Lane.h"
#include "GameMap.h"
#include "RoadLane.h"
#include "SnowLane.h"
#include "WaterLane.h"
#include "RailWayLane.h"
#include "TextStrings.h"

#include <vector>
#include <string>

class WinterMap : public GameMap {
public:
	WinterMap(CrossingRoad* game) : GameMap(game) {};
	
	// when creating first game 
	WinterMap(
		CrossingRoad* pgame,
		GameMode pgameMode
	);

	// when create new game level 
	WinterMap(
		CrossingRoad* pgame,
		GameMapInfo pgameInfo
	) : GameMap(pgame, pgameInfo) {};

	void CreateLanes();
	void ScrollUp();
	void SetScreenColor();

	Lane* GetNewLane(int laneId, Lane* previousLane); // genarate random lane
};
