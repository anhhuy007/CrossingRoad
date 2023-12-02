#pragma once

#include "GameObject.h"
#include "Widget.h"
#include "Values.h"
#include "Sound.h"

class SettingWidget : public GameObject {
	std::vector<Widget::Button> buttons;
	int currentButtonIndex = 0;
	COORD position;
	bool enterClicked = false;
	float totalTime = 0;

	COORD musicPosition = { 81,73 };
	COORD sfxPosition = { 85,104 };
	COORD characterPosition = { 72,150 };
	COORD backPosition = { 80,180 };

	Image cursor = Image(DrawableRes::cursor, Overlapped::DECORATOR);

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

