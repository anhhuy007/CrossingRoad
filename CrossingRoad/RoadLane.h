#pragma once

#ifndef ROAD_LANE_H
#define ROAD_LANE_H

#include "Lane.h"
#include "Vehicle.h"

class RoadLane : public Lane {
	Vehicle* vehicle;
public: 
	RoadLane(
		int id,
		CrossingRoad* game,
		Graphic::Sprite roadSprite = Graphic::Sprite()
	) : Lane(id, game, roadSprite) {
		Graphic::Sprite car = Graphic::Sprite("RedCar.sprite");

		// generate random vehicle
		srand(time(NULL));
		int randomVehicle = rand() % 3;
		MovingDirection randomDirection = (rand() % 2) == 0 ? MovingDirection::LEFT : MovingDirection::RIGHT;

		if (randomVehicle <= 2) {
			vehicle = new Vehicle(car, { 0, short(id * 24 - 144) }, Overlapped::LAND, randomDirection, game);
		}
	};

	virtual void Update(float elapsedTime);
};

#endif // !ROAD_LANE_H