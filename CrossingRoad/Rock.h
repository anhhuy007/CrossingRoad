#pragma once

#include "GameObject.h"
#include "Alignment.h"

class Rock : public GameObject {
public:
	// ----- behaviors -----
	Rock(
		CrossingRoad* game, 
		int planePos,
		int pblockPos
	);

	void Update(float elapsedTime) {};
	void Render() {};

	void MoveDown();

	// ----- properties -----
	GameSpeed axisSpeed = GameSpeed(24, 6, -11, 21);
	Graphic::Sprite rockSprite;
	int lanePos;
	int blockPos;
};

