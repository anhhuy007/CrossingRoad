#pragma once

#ifndef PORTAL_H
#define PORTAL_H

#include "GameObject.h"

class Portal : public GameObject {
	Graphic::Sprite portalSprite;

public: 
	// ---- properties ----
	bool visible = false;
	int lanePos = 0;

	// ---- behaviors ----
	Portal() : GameObject(nullptr) {};
	Portal(CrossingRoad* game);

	void Update(float elapsedTime) {};
	void Render();
};

#endif PORTAL_H

