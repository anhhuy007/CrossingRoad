#pragma once

#ifndef _LEADERBOARD_H_
#define _LEADERBOARD_H_




#include "Animation.h"
#include "GamePlayer.h"
#include "Widget.h"

class LeaderBoard : public CrossingRoad::GameScreen
{
public:
	LeaderBoard(CrossingRoad* game) : GameScreen(game) {};

	// overrided functions 
	bool OnCreate() override;
	bool OnUpdate(float elapsedTime) override;
	bool OnPause()  override { return false; };	// handle ESC key pressed
	bool OnDestroy() override { return false; }



	Image bg;
	Image item;
	Image title;
	Image text1;
	Image text2;

	Image medal1;
	Image medal2;
	Image medal3;

	


};













#endif // !_LEADERBOARD_H_