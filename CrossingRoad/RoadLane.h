#pragma once

#ifndef ROAD_LANE_H
#define ROAD_LANE_H

#include "Lane.h"
#include "Vehicle.h"
#include "Alignment.h"

class RoadLane : public Lane {
	Vehicle vehicle;
	MovingDirection direction;
	bool hasRoadMarking;
	Graphic::Sprite roadMarkingSprite;
	float time = 0.0f;

public: 
	RoadLane(
		int id,
		CrossingRoad* game,
		Graphic::Sprite roadSprite,
		Graphic::Sprite _roadMarkingSprite,
		bool _hasRoadMarking
	) : Lane(id, game, roadSprite, LaneType::ROAD) {
		// generate random vehicle
		direction = (rand() % 2) == 0 ? MovingDirection::LEFT : MovingDirection::RIGHT;
		vehicle = Vehicle(game, id, direction);
		hasRoadMarking = _hasRoadMarking;
		roadMarkingSprite = _roadMarkingSprite;
	};

	void Update(float elapsedTime);
	void Render();
	void ScrollUp();
};

#endif // !ROAD_LANE_H