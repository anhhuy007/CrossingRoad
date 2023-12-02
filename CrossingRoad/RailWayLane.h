#pragma once

#include "Lane.h"
#include "Vehicle.h"

class RailWayLane : public Lane
{
	Vehicle train;
	MovingDirection direction;
	float time = 0;	// manage lane time
	float trainTime = 0;	// manage train time

public: 
	RailWayLane(
		int id,
		CrossingRoad* game,
		Graphic::Sprite railWaySprite
	);

	RailWayLane(
		int id, 
		CrossingRoad* game,
		Graphic::Sprite railWaySprite,
		LaneInfo laneInfo
	);

	void Update(float elapsedTime);
	void Render();
	void ScrollUp();

	// get vehicle
	Vehicle GetVehicle();
};

