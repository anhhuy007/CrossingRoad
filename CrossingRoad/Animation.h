#pragma once

#include "CrossingRoad.h"
#include "Graphic.h"

#include <vector>

#define Image Graphic::Sprite

class Animation {
	CrossingRoad* game = nullptr;
	std::vector<Image> images;
	COORD position;
	int delay;	// delay each frame in milliseconds
	bool isPause = false;
	int frameId = 0;
	float totalTime = 0;

public:
	Animation() = default;
	Animation(
		CrossingRoad* pgame,
		std::vector<Image> pimages,
		COORD pposition,
		int pdelay
	);

	// methods
	void OnPlay(float elapsedTime);	// join animation to new thread
	void OnPause();
	void OnResume();
};

