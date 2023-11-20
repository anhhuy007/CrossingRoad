#pragma once

#ifndef MENU_H
#define MENU_H

#include "Animation.h"
#include "GamePlayer.h"
#include "Widget.h"
#include "MenuWidget.h"

class Menu : public CrossingRoad::GameScreen {
public: 
	Menu(CrossingRoad* game) : GameScreen(game) {};

	// overrided functions 
	bool OnCreate();
	bool OnUpdate(float elapsedTime);
	bool OnDestroy() { return false; };

	Animation meow;
	GamePlayer* chick = nullptr;
	Widget::Text text = Widget::Text(game);
	Image image;
	Widget::Button button = Widget::Button(game);
	MenuWidget menuWidget = MenuWidget(game);
};

#endif // !MENU_H
