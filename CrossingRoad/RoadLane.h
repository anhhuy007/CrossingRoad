#pragma once

#ifndef ROAD_LANE_H
#define ROAD_LANE_H

#include "Lane.h"
#include "Vehicle.h"
#include "Coin.h"
#include "Alignment.h"

class RoadLane : public Lane {
	Vehicle vehicle;
	MovingDirection direction;
	Graphic::Sprite roadMarkingSprite;
	float time = 0.0f;

public: 
	Coin coin;
	bool hasRoadMarking;

	RoadLane(
		int id,
		CrossingRoad* game,
		Graphic::Sprite roadSprite,
		Graphic::Sprite _roadMarkingSprite,
		bool _hasRoadMarking
	);

	void Update(float elapsedTime);
	void Render();
	void ScrollUp();
};

#endif // !ROAD_LANE_H