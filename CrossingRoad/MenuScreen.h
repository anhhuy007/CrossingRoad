#pragma once

#ifndef MENU_H
#define MENU_H

#include "Animation.h"
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

	void InitWidget();

	Image bgImage;
	MenuWidget menuWidget;

	//title
	Animation C;
	Animation R1;
	Animation R2;
	Animation O1;
	Animation O2;
	Animation S1;
	Animation S2;
	Animation I;
	Animation N;
	Animation G;
	Animation R;
	Animation O;
	Animation A;
	Animation D;
};

#endif // !MENU_SCREEN_H
