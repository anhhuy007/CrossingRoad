#pragma once

#include "Animation.h"
#include "Widget.h"
#include "MenuWidget.h"
#include "AboutScreen.h"

class AboutScreen : public CrossingRoad::GameScreen {
public:
	AboutScreen(CrossingRoad* game) : GameScreen(game) {};

	// overrided functions 
	bool OnCreate();
	bool OnUpdate(float elapsedTime);
	bool OnPause() { return true; };
	bool OnDestroy() { return false; };

	Animation N;
	Animation H;
	Animation O;
	Animation M;
	Animation num1a;
	Animation num1b;
	Animation acute;
	Animation aboutAnimation;

	Image image, esc;

	//Text
	Widget::Text design, mssv1, mssv2, mssv3, mssv4, instructor, releasedDate, Version;

	MenuWidget aboutMenuWidget;
};

