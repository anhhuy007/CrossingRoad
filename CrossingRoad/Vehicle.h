#pragma once

#include "GameObject.h"
#include "Alignment.h"
#include "TextStrings.h"

class Vehicle : public GameObject {
public:
	// ----- behaviors -----
	Vehicle() : GameObject({ 0, 0 }, game) {};
	Vehicle(
		CrossingRoad* game, 
		int _id, 
		MovingDirection _direction = MovingDirection::LEFT
	);

	void SetInitPosition();
	void Update(float elapsedTime);
	void Render() {};
	void MoveAhead();

	// ----- properties -----
	bool endOfRoad = false;
	Graphic::Sprite vehicleSprite;
	float vehicleSpeed;
	int lanePos;
	MovingDirection movingDirection = MovingDirection::NONE;
	GameSpeed axisSpeed;
	VehicleType type;
	float time = 0.0f;	
};