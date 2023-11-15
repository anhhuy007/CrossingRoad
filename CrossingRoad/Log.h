#pragma once

#ifndef LOG_H
#define LOG_H

#include "GameObject.h"
#include "Alignment.h"
#include "TextStrings.h"

class Log : public GameObject { 
public:
	Log() : GameObject({ 0, 0 }, game) {};
	Log(
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

	int id;
	bool endOfRoad = false;
	Graphic::Sprite logSprite;
	float logSpeed = 0.01f;
protected:
	MovingDirection movingDirection = MovingDirection::NONE;
	GameSpeed axisSpeed;
	LogType logType;
	float time = 0.0f;
};

#endif //!LOG_H

