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

class StreetMap : public GameMap {
	std::vector<std::string> mapLanes;

	void DrawRoadMarking(int laneId);
public:
	StreetMap(CrossingRoad* game) : GameMap(game) {}
	
	void CreateLanes();
};

#endif // !STREET_MAP_H
