#pragma once

#include "GameObject.h"
#include "Widget.h"
#include "Values.h"
#include "Sound.h"

class MenuWidget : public GameObject {
	std::vector<Widget::Button> buttons;
	int currentButtonIndex = 0;
	COORD position;
	std::vector<COORD> buttonPositions;
	bool enterClicked = false;
	float totalTime = 0;	

public: 
	MenuWidget() : GameObject(nullptr) {};
	MenuWidget(
		CrossingRoad* pgame,
		std::vector<Widget::Button>& pbuttons,
		COORD pposition
	);

	void Render();
	void Update(float elapsedTime);
};

