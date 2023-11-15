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
};


#endif LANE_H
