#pragma once

#ifndef LANE_H
#define LANE_H

#include "GameObject.h"
#include "Values.h"

class Lane : public GameObject {
public:
	int id;
	Graphic::Sprite laneSprite;
	
	Lane(
		int id, 
		CrossingRoad* game,
		Graphic::Sprite laneSprite = Graphic::Sprite()
	) : GameObject(460, 138, { 0, short(id * 15 - 144) }, Overlapped::LAND, game) {
		this->id = id;
		this->laneSprite = laneSprite;
	};
	
	Lane(const Lane& lane) : GameObject(lane) {
		this->id = lane.id;
		this->laneSprite = lane.laneSprite;
	}

	virtual void Update(float elapsedTime);
	virtual void Render();
};


#endif LANE_H
