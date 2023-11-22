#pragma once

#ifndef PLAY_MENU_WIDGET_H
#define PLAY_MENU_WIDGET_H

#include "GameObject.h"
#include "Widget.h"
#include "Values.h"
#include "Sound.h"

class PlayMenuWidget : public GameObject {
	std::vector<Widget::Button> buttons;
	int currentButtonIndex = 0;
	COORD position;
	std::vector<COORD> buttonPositions;
	bool enterClicked = false;
	float totalTime = 0;
public:
	PlayMenuWidget(CrossingRoad* pgame) : GameObject(pgame) {};
	PlayMenuWidget(
		CrossingRoad* pgame,
		std::vector<Widget::Button>& pbuttons,
		COORD pposition
	);

	void Render();
	void Update(float elapsedTime);
};

#endif // !PLAY_MENU_WIDGET_H