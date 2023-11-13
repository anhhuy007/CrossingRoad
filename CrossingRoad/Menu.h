#pragma once

#ifndef MENU_H
#define MENU_H

#include "Animation.h"
#include "GamePlayer.h"


class Menu : public CrossingRoad::GameScreen {
public: 
	Menu(CrossingRoad* game) : GameScreen(game) {};

	// overrided functions 
	bool OnCreate();
	bool OnUpdate(float elapsedTime);
	bool OnDestroy() { return false; };

	Animation meow;
	GamePlayer* chick = nullptr;
};

#endif // !MENU_H
