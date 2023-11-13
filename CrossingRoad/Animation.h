#pragma once

#ifndef ANIMATION_H
#define ANIMATION_H

#include "CrossingRoad.h"
#include "Graphic.h"

#include <chrono>
#include <thread>
#include <vector>

#define Image Graphic::Sprite

class Animation {
	CrossingRoad* game = nullptr;
	std::vector<Image> images;
	COORD position;
	int delay;	// delay each frame in milliseconds
	bool isPause = false;
	int frameId = 0;

	// methods
	void PlayAnimation();	// play animation

public:
	Animation() = default;
	Animation(
		CrossingRoad* pgame,
		std::vector<Image> pimages,
		COORD pposition,
		int pdelay
	);

	// methods
	void OnPlay();	// join animation to new thread
	void OnPause();
	void OnResume();
};

#endif // !ANIMATION_H

