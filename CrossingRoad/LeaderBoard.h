#pragma once

#include "Animation.h"
#include "GamePlayer.h"
#include "Widget.h"
#include "Values.h"
#include "FileIO.h"

#include <filesystem>
#include <algorithm>
#include <iostream>

// ----- Game Screens -----
#include "MenuScreen.h"

class LeaderBoard : public CrossingRoad::GameScreen
{
public:
	LeaderBoard(CrossingRoad* game) : GameScreen(game) {};

	void InitWidget();

	// overrided functions 
	bool OnCreate() override;
	bool OnUpdate(float elapsedTime) override;
	bool OnPause()  override { return true; };	// handle ESC key pressed
	bool OnDestroy() override { return false; }

	Image bg;
	Image item;
	Image title;
	Image text1;
	Image text2;
	Image medal1;
	Image medal2;
	Image medal3;

	class LeaderBoardText {
		CrossingRoad* game;
		COORD position;
		LeaderBoardInfo info;
		Widget::Text playerName;
		Widget::Text score;

	public: 
		LeaderBoardText() {
			game = nullptr;
			position = { 0, 0 };
		}

		LeaderBoardText(
			CrossingRoad* pgame,
			COORD pposition,
			LeaderBoardInfo pinfo,
			int pwidth,
			int pheight,
			TextFont pfont,
			short pcolor
		);

		void Render();
		void SetYPosition(int yPos);
	};

	void GetLeaderBoardInfo();
	std::vector<LeaderBoardInfo> leaderBoardInfos;
	std::vector<LeaderBoardText> levelLBTexts;
	std::vector<LeaderBoardText> endlessLBTexts;
};