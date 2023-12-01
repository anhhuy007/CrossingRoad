#pragma once

#include "Tree.h"
#include "Rock.h"
#include "Lane.h"
#include "Graphic.h"

class GrassLane : public Lane {
	std::vector<Tree> trees;
	std::vector<Rock> rocks;
	short objectCoord[20] = { 0 };

public: 
	GrassLane(
		int id,
		CrossingRoad* game,
		Graphic::Sprite _grassSprite,
		int numberOfTree,
		int numberOfRock
	);

	GrassLane(
		int id,
		CrossingRoad* game,
		Graphic::Sprite _grassSprite,
		LaneInfo laneInfo
	);

	void Render();
	void Update(float elapsedTime);
	void ScrollUp();

	// get trees
	std::vector<Tree> GetTrees();
	std::vector<Rock> GetRocks();
};

