#pragma once

#include "Animation.h"
#include "Widget.h"
#include "SettingWidget.h"
#include "MenuScreen.h"

class SettingScreen : public CrossingRoad::GameScreen {
public:
	SettingScreen(CrossingRoad* game) : GameScreen(game) {};

	// overrided functions 
	bool OnCreate();
	bool OnUpdate(float elapsedTime);
	bool OnPause() { return true; };

	//Animation

	//Image
	Image bgImage;
	Image esc;

	SettingWidget settingWidget = SettingWidget(game);

	Animation S;
	Animation E;
	Animation T1;
	Animation T2;
	Animation I;
	Animation N;
	Animation G;

	Widget::Text music, sfx, character, back, enter;
};
