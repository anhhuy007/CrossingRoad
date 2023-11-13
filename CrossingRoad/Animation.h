#pragma once

#ifndef ANIMATION_H
#define ANIMATION_H

#include <chrono>
#include <thread>
#include <vector>

#include "Graphic.h"
#include "CrossingRoad.h"

#define Image Sprite

using namespace Graphic;

class Animation {
	std::vector<Image> images;
	int delay;	// delay each frame in milliseconds

	// methods
	void PlayAnimation(CrossingRoad* game, COORD position);	// play animation

public: 
	Animation() = default;
	Animation(std::vector<Image> pimages, int pdelay);

	// methods
	void Play(CrossingRoad* game, COORD position);	// join animation to new thread
};

#endif // !ANIMATION_H