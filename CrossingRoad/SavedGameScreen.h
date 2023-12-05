#pragma once

#include "Animation.h"
#include "GamePlayer.h"
#include "Widget.h"
#include "FileIO.h"

#include <filesystem>

class SavedGameScreen : public CrossingRoad::GameScreen
{
public:
	SavedGameScreen(CrossingRoad* game) : GameScreen(game) {};

	void InitWidget();
	std::vector<SavedGameDisplayInfo> GetSavedGameInfo();

	// overrided functions 
	bool OnCreate() override;
	bool OnUpdate(float elapsedTime) override;
	bool OnPause()  override { return true; };	// handle ESC key pressed
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
	COORD hoverPos = { 70, 95 };
	int hoverIndex = 0;
	int itemRange = 0;

	class SavedGameText {
		CrossingRoad* game;
		COORD position;
		SavedGameDisplayInfo info;
		Widget::Text number;
		Widget::Text playerName;
		Widget::Text gameName;
		Widget::Text gameMode;
		Widget::Text score;

	public: 

		SavedGameText() {
			game = nullptr;
			position = { 0, 0 };
		}

		SavedGameText(
			CrossingRoad* _game,
			SavedGameDisplayInfo _info,
			COORD _position,
			int _width,
			int _height,
			TextFont _font,
			short _color
		);

		void Render();
		void SetYPosition(int _position);

	};

	std::vector<SavedGameDisplayInfo> savedGameList;
	std::vector<SavedGameText> savedGameTexts;
	Widget::Text header[5] = {
		Widget::Text(game, "No", { 80, 70 }, 100, 10, TextFont::NORMAL, 15),
		Widget::Text(game, "Player Name", { 110, 70 }, 100, 10, TextFont::NORMAL, 15),
		Widget::Text(game, "Game Name", { 210, 70 }, 100, 10, TextFont::NORMAL, 15),
		Widget::Text(game, "Map Type", { 290, 70 }, 100, 10, TextFont::NORMAL, 15),
		Widget::Text(game, "Score", { 350, 70 }, 100, 10, TextFont::NORMAL, 15)
	};
};
