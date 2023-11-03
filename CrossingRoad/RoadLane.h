#pragma once

#ifndef ROAD_LANE_H
#define ROAD_LANE_H

#include "Lane.h"
#include "Vehicle.h"

class RoadLane : public Lane {
	Vehicle vehicle;
	MovingDirection direction;

public: 
	RoadLane(
		int id,
		CrossingRoad* game,
		Graphic::Sprite roadSprite = Graphic::Sprite()
	) : Lane(id, game, roadSprite) {
		// generate random vehicle
		direction = (rand() % 2) == 0 ? MovingDirection::LEFT : MovingDirection::RIGHT;
		vehicle = Vehicle(game, id, direction);
	};

	virtual void Update(float elapsedTime);
	virtual void Render();
};

#endif // !ROAD_LANE_H