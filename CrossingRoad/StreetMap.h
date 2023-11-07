#pragma once

#ifndef STREET_MAP_H
#define STREET_MAP_H

#include "Lane.h"
#include "GameMap.h"
#include "RoadLane.h"
#include "GrassLane.h"

class StreetMap : public GameMap {
public:
	StreetMap(CrossingRoad* game) : GameMap(game) {}
	
	virtual void CreateLanes();
};

#endif // !STREET_MAP_H
