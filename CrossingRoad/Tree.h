#pragma once

#ifndef TREE_H
#define TREE_H

#include "GameObject.h"
#include "Alignment.h"

class Tree : public GameObject {
public: 
	Graphic::Sprite treeSprite;
	TreeType treeType;

	Tree(CrossingRoad* game, int laneId) : GameObject(game) {
		int randomNumber = rand() % 20;

		if (randomNumber % 2) {
			treeSprite = Graphic::Sprite("Tree1.sprite");
			position = Alignment::getAlignedPosition(
				laneId, 
				randomNumber, 
				{ 11, 41 }, 
				Gravity::CENTRALLY_ALIGNED
			);
			position.X += 1;
			position.Y += 1;
			treeType = TreeType::SMALL_TREE;
			width = 25;
			height = 42;
		}
		else {
			treeSprite = Graphic::Sprite("Tree2.sprite");
			position = Alignment::getAlignedPosition(
				laneId, 
				randomNumber, 
				{ 19, 56 }, 
				Gravity::BOTTOM_CENTER
			);
			position.X -= 8;
			position.Y -= 7;
			treeType = TreeType::BIG_TREE;
			width = 45;
			height = 57;
		}

		treeSprite.setOverlapped(Overlapped::OBSTACLE);
	};
	
	void Update(float elapsedTime) {};
	void Render() {};
};

#endif // !TREE_H

