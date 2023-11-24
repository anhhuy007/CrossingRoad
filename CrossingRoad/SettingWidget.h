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

	Widget::Text music = Widget::Text(game, "MUSIC", { 20,60 }, 25, 34, TextFont::NORMAL);
	Widget::Text sfx = Widget::Text(game, "SFX", { 20,90 }, 15, 34, TextFont::NORMAL);
	Widget::Text character = Widget::Text(game, "CHARACTER", { 20,120 }, 45, 34, TextFont::NORMAL);
	Widget::Text back = Widget::Text(game, "BACK", { 20,130 }, 20, 34, TextFont::NORMAL);

	Graphic::Sprite getSpriteVolumeLevel(int);

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

