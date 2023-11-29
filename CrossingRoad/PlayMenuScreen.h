#pragma once

#include "Animation.h"
#include "Widget.h"
#include "MenuWidget.h"
#include "PlayMenuScreen.h"

class PlayMenuScreen : public CrossingRoad::GameScreen {
public:
	PlayMenuScreen(CrossingRoad* game) : GameScreen(game) {};

	// overrided functions 
	bool OnCreate();
	bool OnUpdate(float elapsedTime);
	bool OnDestroy() { return false; };

	Image bgImage;
	MenuWidget playMenuWidget;
};

