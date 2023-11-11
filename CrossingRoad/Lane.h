#pragma once

#ifndef LANE_H
#define LANE_H

#include "GameObject.h"
#include "Values.h"
#include "Vehicle.h"

class Lane : public GameObject {
protected:
	int id;
	Graphic::Sprite laneSprite;

public:
	Lane(
		int id, 
		CrossingRoad* game,
		Graphic::Sprite laneSprite = Graphic::Sprite()
	) : GameObject(460, 138, { 0, short(id * 24 - 144) }, game) {
		this->id = id;
		this->laneSprite = laneSprite;
		this->game = game;
	};
	
	Lane(const Lane& lane) : GameObject(lane) {
		this->id = lane.id;
		this->laneSprite = lane.laneSprite;
		this->game = lane.game;
	}

	virtual void Update(float elapsedTime) = 0;
	virtual void Render() = 0;
};


#endif LANE_H
