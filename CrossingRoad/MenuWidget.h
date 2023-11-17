#pragma once

#ifndef MENU_WIDGET_H
#define MENU_WIDGET_H

#include "GameObject.h"
#include "Widget.h"
#include "Values.h"

class MenuWidget : public GameObject {
	std::vector<Widget::Button> buttons;
	int currentButtonIndex = 0;
	COORD position;
	std::vector<COORD> buttonPositions;

public: 
	MenuWidget(CrossingRoad* pgame) : GameObject(pgame) {};
	MenuWidget(
		CrossingRoad* pgame,
		vector<Widget::Button> pbuttons,
		COORD pposition
	);

	void Render();
	void Update(float elapsedTime);
};

#endif // !MENU_WIDGET_H

