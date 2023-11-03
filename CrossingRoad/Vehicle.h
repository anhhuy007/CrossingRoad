#pragma once

#ifndef VEHICLE_H
#define VEHICLE_H

#include "GameObject.h"

class Vehicle : public GameObject {
public:
	Vehicle() : GameObject({ 0, 0 }, Overlapped::VEHICLE, game) {};
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

protected:
	int id;
	MovingDirection movingDirection = MovingDirection::NONE;
	GameSpeed axisSpeed;
	VehicleType type;
	float vehicleSpeed = 0.01f;
	float time = 0.0f;
};

#endif // !VEHICLE_H