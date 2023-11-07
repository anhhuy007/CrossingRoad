#pragma once

#ifndef GRASS_LANE_H
#define GRASS_LANE_H

#include "Tree.h"
#include "Lane.h"
#include "Graphic.h"

class GrassLane : public Lane {
public: 
	vector<Tree> trees;
	GrassLane(
		int id,
		CrossingRoad* game,
		Graphic::Sprite _grassSprite
	) : Lane(id, game, _grassSprite) {
		// generate random tree
		int numberOfTree = rand() % 10 + 3;

		for (int i = 2; i < numberOfTree; i++) {
			trees.push_back(Tree(game, id));
		}
	};

	void Render() {
		game->RenderSprite(laneSprite, position);
		for (int i = 0; i < trees.size(); i++) {
			game->RenderSprite(trees[i].treeSprite, trees[i].getPosition());
		}
	}

	void Update(float elapsedTime) {};
};

#endif // !GRASS_LANE_H

