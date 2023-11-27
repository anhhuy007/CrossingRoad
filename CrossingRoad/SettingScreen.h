#pragma once

#ifndef SETTING_SCREEN_H
#define SETTING_SCREEN_H

#include "Animation.h"
#include "GamePlayer.h"
#include "Widget.h"
#include "SettingWidget.h"

class SettingScreen : public CrossingRoad::GameScreen {
public:
	SettingScreen(CrossingRoad* game) : GameScreen(game) {};

	// overrided functions 
	bool OnCreate();
	bool OnUpdate(float elapsedTime);
	bool OnDestroy() { return false; };

	//Animation

	//Image
	Image image;

	SettingWidget settingWidget = SettingWidget(game);

	Animation S;
	Animation E;
	Animation T1;
	Animation T2;
	Animation I;
	Animation N;
	Animation G;

};

#endif // !SETTING_SCREEN_H
