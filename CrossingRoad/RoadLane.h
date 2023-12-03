#pragma once

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

	RoadLane(
		int id, 
		CrossingRoad* game,
		Graphic::Sprite roadSprite,
		LaneInfo laneInfo,
		bool _hasRoadMarking
	);

	void Update(float elapsedTime);
	void Render();
	void ScrollUp();

	// get vehicle
	Vehicle GetVehicle();
};
