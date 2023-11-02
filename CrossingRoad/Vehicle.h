#pragma once

#ifndef VEHICLE_H
#define VEHICLE_H

#include "GameObject.h"

class Vehicle : public GameObject {
public:
	Vehicle();

	Vehicle(
		const COORD& coord,
		const int& width,
		const int& height,
		const int& overlapped,
		CrossingRoad* game
	) : GameObject(width, height, coord, overlapped, game) {};

	Vehicle(
		Graphic::Sprite vehicleSprite,	
		const COORD& coord,
		const int& overlapped,
		MovingDirection direction,
		CrossingRoad* game
	) : GameObject(coord, overlapped, game) {
		this->sprite = vehicleSprite;
		sprite.setOverlapped(overlapped);
		width = sprite.getWidth();
		height = sprite.getHeight();
		axisSpeed = GameSpeed(4, 1, 0, 0);
		movingDirection = direction;
	}

	virtual void Update(float elapsedTime);
	virtual void Render();
	//void Move();

	short getX() { return position.X; }
	short getY() { return position.Y; }

protected:
	MovingDirection movingDirection = MovingDirection::NONE;
	Graphic::Sprite sprite;
	GameSpeed axisSpeed;
	bool endOfRoad = false;
};

#endif // !VEHICLE_H