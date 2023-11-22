#pragma once

#include "GameObject.h"
#include "Alignment.h"

class Coin : public GameObject {
public: 
	// ---- properties ----
	Graphic::Sprite coinSprite;
	int lanePos;
	GameSpeed axisSpeed;
	bool isCollected = false;

	// ---- methods ----
	Coin();
	Coin(
		CrossingRoad* game,
		int planePos
	);

	void Update(float elapsedTime);
	void Render();
	void MoveDown();
};

