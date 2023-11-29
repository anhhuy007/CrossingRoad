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
	bool OnDestroy() { return false; };

	Image image;

	//Text
	Widget::Text design, mssv1, mssv2, mssv3, mssv4, instructor, releasedDate, Version;

	MenuWidget aboutMenuWidget = MenuWidget(game);
};

#endif // !ABOUT_SCREEN_H


