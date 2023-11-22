#pragma once

#ifndef PLAY_MENU_SCREEN_H
#define PLAY_MENU_SCREEN_H

#include "Animation.h"
#include "GamePlayer.h"
#include "Widget.h"
#include "PlayMenuWidget.h"
#include "PlayMenuScreen.h"

class PlayMenuScreen : public CrossingRoad::GameScreen {
public:
	PlayMenuScreen(CrossingRoad* game) : GameScreen(game) {};

	// overrided functions 
	bool OnCreate();
	bool OnUpdate(float elapsedTime);
	bool OnDestroy() { return false; };

	Animation meow;
	Image image;
	PlayMenuWidget playMenuWidget = PlayMenuWidget(game);
};

#endif // !PLAY_MENU_SCREEN_H
