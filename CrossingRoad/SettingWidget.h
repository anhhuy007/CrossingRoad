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

