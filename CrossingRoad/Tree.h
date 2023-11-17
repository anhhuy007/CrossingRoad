#pragma once

#ifndef TREE_H
#define TREE_H

#include "GameObject.h"
#include "Alignment.h"

class Tree : public GameObject {
public: 
	Graphic::Sprite treeSprite;
	TreeType treeType;
	int lanePos;
	int blockPos;

	Tree(CrossingRoad* game, int laneId) : GameObject(game) {
		int randomNumber = rand() % 20;

		lanePos = laneId;
		blockPos = randomNumber;

		if (randomNumber % 2) {
			treeSprite = Graphic::Sprite(DrawableRes::SmallTree);
			position = Alignment::getAlignedPosition(
				laneId, 
				randomNumber, 
				{ 10, 40 }, 
				Gravity::CENTRALLY_ALIGNED
			);
			treeType = TreeType::SMALL_TREE;
			width = 25;
			height = 42;
		}
		else {
			treeSprite = Graphic::Sprite(DrawableRes::BigTree);
			position = Alignment::getAlignedPosition(
				laneId, 
				randomNumber, 
				{ 26, 63 }, 
				Gravity::BOTTOM_CENTER
			);
			treeType = TreeType::BIG_TREE;
			width = 45;
			height = 57;
		}

		treeSprite.SetOverlapped(Overlapped::OBSTACLE);
	};
	
	void Update(float elapsedTime) {};
	void Render() {};
};

#endif // !TREE_H

