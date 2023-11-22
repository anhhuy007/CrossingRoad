#pragma once


#ifndef SPLASHSCREEN_H
#define SPLASHSCREEN_H

#include "Animation.h"
#include "GamePlayer.h"
#include "Widget.h"


class SplashScreen : public CrossingRoad::GameScreen
{
public:
	SplashScreen(CrossingRoad* game) : GameScreen(game) {};

	// overrided functions 
	bool OnCreate() override;
	bool OnUpdate(float elapsedTime) override;
	bool OnPause()  override { return false; };	// handle ESC key pressed
	bool OnDestroy() override { return false; }

	Animation chicken;
	Animation N;
	Animation H;
	Animation O;
	Animation M;
	Animation num1a;
	Animation num1b;
	Animation acute;
	Animation bubbles;

	Image textA1;
	Image textA2;
	Image bg;
};





#endif //SPLASHSCREEN_H