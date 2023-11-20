#pragma once

#ifndef WATER_LANE_H
#define WATER_LANE_H

#include "Lane.h"
#include "Log.h"

#include <vector>

class WaterLane : public Lane {
	MovingDirection direction;

public:
	Log log;

	WaterLane(
		int id,
		CrossingRoad* game,
		Graphic::Sprite waterSprite = Graphic::Sprite()
	) : Lane(id, game, waterSprite, LaneType::WATER) {
		// generate random log
		direction = (rand() % 2) == 0 ? MovingDirection::LEFT : MovingDirection::RIGHT;
		log = Log(game, id, direction);
		setCollisionPoints(
			Factory::GetObjectCollisionPoints(ObjectType::WATER)
		);
	};

	void Update(float elapsedTime);
	void Render();
	void ScrollUp();
};

#endif // !WATER_LANE_H

