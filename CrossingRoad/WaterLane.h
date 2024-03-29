#pragma once

#include "Lane.h"
#include "Log.h"

#include <vector>

class WaterLane : public Lane {

public:
	MovingDirection direction;
	Log log;
	WaterLane(
		int id,
		CrossingRoad* game,
		MovingDirection pdirection,
		Graphic::Sprite waterSprite = Graphic::Sprite()
	);

	WaterLane(
		int id,
		CrossingRoad* game,
		Graphic::Sprite waterSprite,
		LaneInfo laneInfo
	);

	void Update(float elapsedTime);
	void Render();
	void ScrollUp();

	// get log
	Log GetLog();
};

