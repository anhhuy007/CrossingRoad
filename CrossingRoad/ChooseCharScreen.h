#pragma once

#ifndef _CHOOSECHARSCREEN_H_
#define _CHOOSECHARSCREEN_H_

#include "Animation.h"
#include "GamePlayer.h"


class ChooseCharScreen : public CrossingRoad::GameScreen
{

public:
	ChooseCharScreen(CrossingRoad* game) : GameScreen(game) {};

	// overrided functions 
	bool OnCreate() override;
	bool OnUpdate(float elapsedTime) override;
	bool OnPause()  override { return false; };	// handle ESC key pressed
	bool OnDestroy() override { return false; }


};


#endif // !_CHOOSECHARSCREEN_H_