#pragma once

#include "Animation.h"
#include "Widget.h"
#include "MenuWidget.h"
#include "PlayMenuScreen.h"

class PlayMenuScreen : public CrossingRoad::GameScreen {
public:
	PlayMenuScreen(CrossingRoad* game) : GameScreen(game) {};

	// overrided functions 
	bool OnCreate();
	bool OnUpdate(float elapsedTime);
	bool OnPause() { return true; };
	bool OnDestroy() { return false; };

	void InitWidget();

	void OnLevelModeClicked();
	void OnEndlessModeClicked();
	void OnLoadGameClicked();
	std::string GetSavedGameName();

	Image bgImage;
	MenuWidget playMenuWidget;
};

