#pragma once

#include "GameObject.h"
#include "Alignment.h"
#include "TextStrings.h"

class Log : public GameObject { 
public:
	// ----- behaviors -----
	Log() : GameObject({ 0, 0 }, game) {};
	Log(
		CrossingRoad* game,
		int _id,
		MovingDirection _direction = MovingDirection::LEFT
	);
	Log(const Log& other) : GameObject(other.game) {
		lanePos = other.lanePos;
		logSpeed = other.logSpeed;
		movingDirection = other.movingDirection;
	};

	void SetSprite(Graphic::Sprite _sprite);
	void SetInitPosition();

	void Update(float elapsedTime);
	void Render() {};

	// ----- attributes -----
	int lanePos;
	bool endOfRoad = false;
	Graphic::Sprite logSprite;
	float logSpeed = 0.01f;
	GameSpeed axisSpeed;
	MovingDirection movingDirection = MovingDirection::NONE;
	float time = 0.0f;
};

