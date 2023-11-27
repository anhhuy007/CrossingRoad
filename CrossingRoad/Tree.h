#pragma once

#ifndef TREE_H
#define TREE_H

#include "GameObject.h"
#include "Alignment.h"

class Tree : public GameObject {
public: 
	// ----- behaviors -----
	Tree(
		CrossingRoad* game,
		int planePos,
		int pblockPos,
		TreeType ptreeType,
		Graphic::Sprite psprite
	);
	
	void Update(float elapsedTime) {};
	void Render() {};

	// ----- properties -----
	Graphic::Sprite treeSprite;
	TreeType treeType;
	int lanePos;
	int blockPos;
};

#endif // !TREE_H

