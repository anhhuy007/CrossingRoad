#pragma once

#ifndef GRASS_LANE_H
#define GRASS_LANE_H

#include "Tree.h"
#include "Lane.h"
#include "Graphic.h"

class GrassLane : public Lane {
	vector<Tree> trees;
public: 
	GrassLane(
		int id,
		CrossingRoad* game,
		Graphic::Sprite _grassSprite
	) : Lane(id, game, _grassSprite, LaneType::GRASS) {
		// generate random tree
		int numberOfTree = rand() % 5 + 1;
		for (int i = 2; i < numberOfTree; i++) {
			trees.push_back(Tree(game, id));
		}
	};

	void Render();
	void Update(float elapsedTime);
	void ScrollUp();
};

#endif // !GRASS_LANE_H

