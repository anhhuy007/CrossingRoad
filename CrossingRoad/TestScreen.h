#pragma once

#include "Widget.h"
#include "PlayMenuScreen.h"

class TestScreen : public CrossingRoad::GameScreen {
public:
	TestScreen(CrossingRoad* game) : GameScreen(game) {};

	// overrided functions 
	bool OnCreate();
	bool OnUpdate(float elapsedTime);
	bool OnDestroy() { return false; };

	Widget::Dialog dialog;
	Image bgImage;
};

