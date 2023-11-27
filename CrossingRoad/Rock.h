#pragma once

#include "GameObject.h"
#include "Alignment.h"

class Rock : public GameObject {
public:
	// ----- behaviors -----
	Rock(
		CrossingRoad* game, 
		int planePos,
		int pblockPos,
		Graphic::Sprite pSprite
	);

	void Update(float elapsedTime) {};
	void Render() {};


	// ----- properties -----
	Graphic::Sprite rockSprite;
	int lanePos;
	int blockPos;
};

