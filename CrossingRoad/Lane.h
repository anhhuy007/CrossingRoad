#pragma once

#include "GameObject.h"
#include "Values.h"
#include "Vehicle.h"

class Lane : public GameObject {
public:
	Graphic::Sprite laneSprite;
	int id;
	LaneType laneType;

	Lane(
		int id,
		CrossingRoad* game,
		Graphic::Sprite laneSprite,
		LaneType laneType
	);
	
	Lane(const Lane& lane);

	virtual void Update(float elapsedTime) = 0;
	virtual void Render() = 0;
	virtual void ScrollUp() = 0;
	
	// private methods
private:
	COORD GetInitPosition(int _id) {
		return { 0, short(_id * 24 - 144) };
	}
};