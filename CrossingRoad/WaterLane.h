#pragma once

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
		SetCollisionPoints(Factory::GetObjectCollisionPoints(ObjectType::WATER));
	};

	void Update(float elapsedTime);
	void Render();
	void ScrollUp();
};

