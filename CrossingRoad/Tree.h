#pragma once

#include "GameObject.h"
#include "Alignment.h"

class Tree : public GameObject {
public: 
	// ----- behaviors -----
	Tree(
		CrossingRoad* game,
		int planePos,
		int pblockPos,
		ObjectType pobjType,
		Graphic::Sprite psprite
	);
	
	void Update(float elapsedTime) {};
	void Render() {};

	// ----- properties -----
	Graphic::Sprite treeSprite;
	int lanePos;
	int blockPos;
};

