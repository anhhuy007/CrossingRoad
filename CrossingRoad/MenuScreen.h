#pragma once

#ifndef MENU_H
#define MENU_H

#include "Animation.h"
#include "GamePlayer.h"
#include "Widget.h"
#include "MenuWidget.h"
#include "SettingScreen.h"
#include "AboutScreen.h"

class MenuScreen : public CrossingRoad::GameScreen {
public:
	MenuScreen(CrossingRoad* game) : GameScreen(game) {};

	// overrided functions 
	bool OnCreate();
	bool OnUpdate(float elapsedTime);
	bool OnDestroy() { return false; };

	Animation meow;
	Image image;
	MenuWidget menuWidget = MenuWidget(game);
};

#endif // !MENU_SCREEN_H
