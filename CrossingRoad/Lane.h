#pragma once

#ifndef LANE_H
#define LANE_H

#include "GameObject.h"
#include "Values.h"
#include "Vehicle.h"

class Lane : public GameObject {
protected:
	Graphic::Sprite laneSprite;

public:
	int id;
	LaneType laneType;
	bool isScrolling = false;
	COORD expectedPosition;	// position after scrolling

	Lane(
		int id, 
		CrossingRoad* game,
		Graphic::Sprite laneSprite,
		LaneType laneType
	) : GameObject(460, 138, { 0, short(id * 24 - 144) }, game) {
		this->id = id;
		this->laneSprite = laneSprite;
		this->game = game;
		this->laneType = laneType;
		this->expectedPosition = GetInitPosition(id);
	};
	
	Lane(const Lane& lane) : GameObject(lane) {
		this->id = lane.id;
		this->laneSprite = lane.laneSprite;
		this->game = lane.game;
		this->laneType = lane.laneType;
	}

	virtual void Update(float elapsedTime) = 0;
	virtual void Render() = 0;
	virtual void ScrollUp() = 0;
	
	// private methods
private:
	COORD GetInitPosition(int _id) {
		return { 0, short(_id * 24 - 144) };
	}
};


#endif LANE_H
