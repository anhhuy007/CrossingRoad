#pragma once

#ifndef LANE_H
#define LANE_H

#include "GameObject.h"

class Lane : public GameObject {
public:
	Lane();
	Lane(int id, CrossingRoad* game);
	~Lane();

	virtual void Update(float elapsedTime);
	virtual void Render();
};


#endif LANE_H
