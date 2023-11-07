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
			position = Alignment::getAlignedPosition(laneId, randomNumber, { 7, 19 }, Gravity::CENTRALLY_ALIGNED);
			treeType = TreeType::SMALL_TREE;
			position.X += 22;
			position.Y -= 10;
			width = 25;
			height = 42;
		}
		else {
			treeSprite = Graphic::Sprite("Tree2.sprite");
			position = Alignment::getAlignedPosition(laneId, randomNumber, { 23, 26 }, Gravity::BOTTOM_CENTER);
			position.X += 22;
			position.Y -= 51;
			treeType = TreeType::BIG_TREE;
			width = 45;
			height = 57;
		}

		treeSprite.setOverlapped(Overlapped::VEHICLE);
		overlapped = Overlapped::OBSTACLE;
	};
	
	//Tree(CrossingRoad* game, int laneId, TreeType _treeType) : GameObject(game) {
	//	int randomNumber = ()

	//	if (treeType == TreeType::SMALL_TREE) {
	//		treeSprite = Graphic::Sprite("Tree1.sprite");
	//		position = Alignment::getAlignedPosition(laneId, randomNumber, { 7, 19 }, Gravity::CENTRALLY_ALIGNED);
	//		position.X += 22;
	//		position.Y -= 10;
	//		width = 25;
	//		height = 42;
	//	}
	//	else {
	//		treeSprite = Graphic::Sprite("Tree2.sprite");
	//		position = Alignment::getAlignedPosition(laneId, randomNumber, { 23, 26 }, Gravity::BOTTOM_CENTER);
	//		position.X += 22;
	//		position.Y -= 51;
	//		width = 45;
	//		height = 57;
	//	}

	//	treeSprite.setOverlapped(Overlapped::VEHICLE);
	//	overlapped = Overlapped::OBSTACLE;
	//};

	void Update(float elapsedTime) {};
	void Render() {};
};

#endif // !TREE_H

