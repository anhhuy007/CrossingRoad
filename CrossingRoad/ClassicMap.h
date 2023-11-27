#pragma once

#ifndef STREET_MAP_H
#define STREET_MAP_H

#include "Lane.h"
#include "GameMap.h"
#include "RoadLane.h"
#include "GrassLane.h"
#include "WaterLane.h"
#include "TextStrings.h"

#include <vector>
#include <string>

class ClassicMap : public GameMap {
public:
	ClassicMap(CrossingRoad* game) : GameMap(game) {};
	
	void CreateLanes();
	void ScrollUp();
	void SetScreenColor();

	Lane* GetNewLane(int laneId, LaneType previousLane); // genarate random lane
};

#endif // !STREET_MAP_H
