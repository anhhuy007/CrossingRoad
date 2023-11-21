#pragma once

#ifndef GRASS_LANE_H
#define GRASS_LANE_H

#include "Tree.h"
#include "Lane.h"
#include "Graphic.h"

class GrassLane : public Lane {
	std::vector<Tree> trees;
public: 
	GrassLane(
		int id,
		CrossingRoad* game,
		Graphic::Sprite _grassSprite,
		int numberOfTree
	);

	void Render();
	void Update(float elapsedTime);
	void ScrollUp();
};

#endif // !GRASS_LANE_H

