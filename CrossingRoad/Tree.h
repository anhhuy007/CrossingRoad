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
		TreeType ptreeType
	);
	
	void Update(float elapsedTime) {};
	void Render() {};

	void MoveDown();

	// ----- properties -----
	GameSpeed axisSpeed = GameSpeed(24, 6, -11, 21);
	Graphic::Sprite treeSprite;
	TreeType treeType;
	int lanePos;
	int blockPos;
};

#endif // !TREE_H

