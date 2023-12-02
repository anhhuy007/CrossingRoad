#pragma once

#include "GameObject.h"
#include "Alignment.h"
#include "TextStrings.h"

class Vehicle : public GameObject {
public:
	// ----- behaviors -----
	Vehicle() : GameObject(nullptr) {};
	
	// for creating new random vehicle
	Vehicle(
		CrossingRoad* game,
		int _id,
		MovingDirection _direction = MovingDirection::LEFT
	);

	// for creating a particular vehicle
	Vehicle(
		CrossingRoad* game,
		int _id,
		MovingDirection _direction,
		ObjectType _objType
	);


	// for loading from file
	Vehicle(
		CrossingRoad* game,
		int _lanePos,
		MovingDirection _direction,
		ObjectInfo _info
	);

	void SetInitPosition();
	void Update(float elapsedTime);
	void Render();
	void MoveAhead();

	// ----- properties -----
	bool endOfRoad = false;
	Graphic::Sprite vehicleSprite;
	float vehicleSpeed;
	int lanePos;
	MovingDirection movingDirection = MovingDirection::NONE;
	GameSpeed axisSpeed;	// for moving horizontally
	float time = 0.0f;
};