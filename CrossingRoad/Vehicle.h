#pragma once

#ifndef VEHICLE_H
#define VEHICLE_H

#include "GameObject.h"
#include "Alignment.h"
#include "TextStrings.h"

class Vehicle : public GameObject {
public:
	Vehicle() : GameObject({ 0, 0 }, game) {};
	Vehicle(
		CrossingRoad* game, 
		int _id, 
		MovingDirection _direction = MovingDirection::LEFT
	);

	void setSprite(Graphic::Sprite _sprite);
	void setInitPosition();

	void Update(float elapsedTime);
	void Render();

	short getX() { return position.X; }
	short getY() { return position.Y; }

	bool endOfRoad = false;
	Graphic::Sprite vehicleSprite;
	float vehicleSpeed = 0.01f;
	int lanePos;
	MovingDirection movingDirection = MovingDirection::NONE;
	GameSpeed axisSpeed;
protected:
	VehicleType type;
	float time = 0.0f;
};

#endif // !VEHICLE_H