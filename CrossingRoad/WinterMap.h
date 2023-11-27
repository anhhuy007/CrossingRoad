#pragma once

#ifndef WINTER_MAP_H
#define WINTER_MAP_H

#include "Lane.h"
#include "GameMap.h"
#include "RoadLane.h"
#include "SnowLane.h"
#include "WaterLane.h"
#include "TextStrings.h"

#include <vector>
#include <string>

class WinterMap : public GameMap {
	Graphic::Sprite snowlane;
	Graphic::Sprite waterlane;
	Graphic::Sprite roadlane;
	Graphic::Sprite roadMarking;

public:
	WinterMap(CrossingRoad* game) : GameMap(game) {};

	void CreateLanes();
	void ScrollUp();
	void SetScreenColor();

	Lane* GetNewLane(int laneId, LaneType previousLane); // genarate random lane
};

#endif // !WINTER_MAP_H
