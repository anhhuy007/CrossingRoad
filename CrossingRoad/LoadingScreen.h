#pragma once

#include "CrossingRoad.h"
#include "Widget.h"
#include "Animation.h"

class LoadingScreen : public CrossingRoad::GameScreen
{
	Animation loadingAnimation, chickAnimation;
	Image bgImage, tip;
	float time = 0;
	bool doneLoading = false;

public:
	LoadingScreen(CrossingRoad* game) : GameScreen(game) {};

	bool OnCreate() override;
	bool OnUpdate(float elapsedTime) override;
	bool OnPause() override { return false; };
	bool OnDestroy() override { return false; };

	void InitWidget();
};

