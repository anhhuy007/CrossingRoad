#pragma once

#include "Lane.h"
#include "GameMap.h"
#include "RoadLane.h"
#include "SnowLane.h"
#include "WaterLane.h"
#include "TextStrings.h"

#include <vector>
#include <string>

class WinterMap : public GameMap {
public:
	WinterMap(CrossingRoad* game) : GameMap(game) {};

	void CreateLanes();
	void ScrollUp();
	void SetScreenColor();

	Lane* GetNewLane(int laneId, LaneType previousLane); // genarate random lane
};
