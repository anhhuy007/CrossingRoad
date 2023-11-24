#pragma once

#ifndef SETTING_WIDGET_H
#define SETTING_WIDGET_H

#include "GameObject.h"
#include "Widget.h"
#include "Values.h"
#include "Sound.h"

class SettingWidget : public GameObject {
	std::vector<Widget::Button> buttons;
	int currentButtonIndex = 0;
	COORD position;
	std::vector<COORD> buttonPositions;
	bool enterClicked = false;
	float totalTime = 0;

	COORD musicPosition = { 81,73 };
	COORD sfxPosition = { 85,104 };
	COORD characterPosition = { 72,150 };
	COORD backPosition = { 80,180 };

	Image cursor = Image(DrawableRes::cursor, Overlapped::DECORATOR);

	Widget::Text music = Widget::Text(game, "MUSIC", { 111,73 }, 25, 34, TextFont::NORMAL);
	Widget::Text sfx = Widget::Text(game, "SFX", { 115,104 }, 15, 34, TextFont::NORMAL);
	Widget::Text character = Widget::Text(game, "CHARACTER", { 102,150 }, 45, 34, TextFont::NORMAL);
	Widget::Text back = Widget::Text(game, "BACK", { 110,180}, 20, 34, TextFont::NORMAL);


	COORD getCursorPosition(int);
	Graphic::Sprite getSpriteVolumeLevel(int,bool);

public:
	SettingWidget(CrossingRoad* pgame) : GameObject(pgame) {};
	SettingWidget(
		CrossingRoad* pgame,
		std::vector<Widget::Button>& pbuttons,
		COORD pposition
	);

	void Render();
	void Update(float elapsedTime);
};
#endif // !SETTIING_WIDGET_H

