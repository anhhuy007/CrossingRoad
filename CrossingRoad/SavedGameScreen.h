#pragma once

#ifndef _SAVEDGAMESCREEN_H_
#define _SAVEDGAMESCREEN_H_


#include "Animation.h"
#include "GamePlayer.h"
#include "Widget.h"

class SavedGameScreen : public CrossingRoad::GameScreen
{
public:
	SavedGameScreen(CrossingRoad* game) : GameScreen(game) {};

	// overrided functions 
	bool OnCreate() override;
	bool OnUpdate(float elapsedTime) override;
	bool OnPause()  override { return false; };	// handle ESC key pressed
	bool OnDestroy() override { return false; }

	//declare
	Animation S;
	Animation A1;
	Animation V;
	Animation E;
	Animation D;

	Animation G;
	Animation A2;
	Animation M;
	Animation E1;
	Animation E2;
	Image bg;
	Image headerItem;
	Image listItem;
	Image book;
	Image cat;
	Animation hover;


};

#endif // !_SAVEDGAMESCREEN_H_