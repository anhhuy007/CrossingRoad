#pragma once

// ----- STANDARD INCLUDES -----
#include <Windows.h>
#include <vector>

// ----- MY CLASS INCLUDES -----
#include "Graphic.h"
#include "CrossingRoad.h"
#include "GameEngine.h"
#include "Factory.h"

#define CollisionPoint std::pair<COORD, int>

class GameObject {
protected:
	int width;
	int height;
	COORD position;	// real object position in console (top left coordinate)
	CrossingRoad* game = nullptr;
	std::vector<CollisionPoint> collisionPoints;	// points of object collision
	GameSpeed moveDownSpeed = GameSpeed(0, 0, -11, 21);
	ObjectType objType = ObjectType::NONE;
public:
	GameObject(
		int _width,
		int _height,
		COORD _position,
		CrossingRoad* _game
	) {
		this->width = _width;
		this->height = _height;
		this->position = _position;
		this->game = _game;
	}

	GameObject(
		COORD _position,
		CrossingRoad* _game
	) {
		this->height = 0;
		this->width = 0;
		this->position = _position;
		this->game = _game;
	}

	GameObject(CrossingRoad* _game) {
		this->height = 0;
		this->width = 0;
		this->position = { 0, 0 };
		this->game = _game;
	}

	GameObject(CrossingRoad* _game, ObjectType _type) {
		this->height = 0;
		this->width = 0;
		this->position = { 0, 0 };
		this->game = _game;
		this->objType = _type;
	}
	
	// ----- Getters -----
	int getWidth();
	int getHeight();
	COORD getPosition();
	ObjectType getObjType() const;

	// ----- Setters -----
	void setPosition(COORD _position);
	void setHeight(int _height);
	void setWidth(int _width);
	void SetCollisionPoints(std::vector<CollisionPoint>_collisionPoints);

	void WriteCollisionPoints();
	void MoveDown(int &planePos); // move object down by 1 unit when map scrolls down

	// ----- Methods -----
	virtual void Update(float elapsedTime) = 0; 
	virtual void Render() = 0;	// render object in a current state to console
};
