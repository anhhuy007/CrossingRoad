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

	Image onToggle;
	Image offToggle;

	SettingWidget settingWidget = SettingWidget(game);
};

#endif // !SETTING_SCREEN_H
