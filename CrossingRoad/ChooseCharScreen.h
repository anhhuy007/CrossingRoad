#pragma once

#ifndef _CHOOSECHARSCREEN_H_
#define _CHOOSECHARSCREEN_H_

#include "Animation.h"
#include "GamePlayer.h"
#include "MenuScreen.h"


class ChooseCharScreen : public CrossingRoad::GameScreen
{

public:
	ChooseCharScreen(CrossingRoad* game) : GameScreen(game) {};

	// overrided functions 
	bool OnCreate() override;
	bool OnUpdate(float elapsedTime) override;
	bool OnPause()  override { return true; };	// handle ESC key pressed
	bool OnDestroy() override { return false; }

	Image char1;
	Image char2;
	Image char3;

	std::vector<int> colors1;
	std::vector<int> colors2;
	std::vector<int> colors3;

	int currentChar;

};


#endif // !_CHOOSECHARSCREEN_H_