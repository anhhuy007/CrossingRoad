#pragma once

#include "Tree.h"
#include "Rock.h"
#include "Lane.h"
#include "Graphic.h"

class SnowLane : public Lane {
	std::vector<Tree> trees;
	std::vector<Rock> rocks;
	short objectCoord[20] = { 0 };

public:
	SnowLane(
		int id,
		CrossingRoad* game,
		Graphic::Sprite _snowSprite,
		int numberOfTree,
		int numberOfRock
	);

	SnowLane(
		int id,
		CrossingRoad* game,
		Graphic::Sprite _snowSprite,
		LaneInfo laneInfo
	);

	void Render();
	void Update(float elapsedTime);
	void ScrollUp();

	std::vector<Tree> GetTrees();
	std::vector<Rock> GetRocks();
};

