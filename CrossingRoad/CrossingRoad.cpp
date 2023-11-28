#include "CrossingRoad.h"

// ----- Game Screens -----
#include "MenuScreen.h"
#include "SplashScreen.h"
#include "SavedGameScreen.h"
#include "AboutScreen.h"
#include "LeaderBoard.h"


// ----- Game Maps -----
#include "ClassicMap.h"
#include "WinterMap.h"

void CrossingRoad::Init() {
	// ----- Init game -----

	GameEngine::BuildConsole();	
	Navigation::To(new LeaderBoard(this));
}

bool CrossingRoad::GameCreate() {
	// ----- Create new game -----


	return true;
}

bool CrossingRoad::GameUpdate(float elapsedTime) {
	// ----- Game pause -----
	if (inputHandle->keyState_[Keyboard::ESCAPE_KEY].isPressed) {
		if (Navigation::OnScreenPause() == false)
			return Navigation::OnScreenDestroy();
	}

	// ------ Game Update -----
	return Navigation::OnScreenUpdate(elapsedTime);
}

void CrossingRoad::Navigation::To(GameScreen* pscreen) {
	// destroy current screen to navigate to new screen
	if (currentScreen_ != nullptr) {
		currentScreen_->OnDestroy();
	}

	currentScreen_ = pscreen;
	currentScreen_->OnCreate();
}

bool CrossingRoad::Navigation::OnScreenCreate() {
	return currentScreen_->OnCreate();
}

bool CrossingRoad::Navigation::OnScreenUpdate(float elapsedTime) {
	if (currentScreen_ == nullptr) return true;

	return currentScreen_->OnUpdate(elapsedTime);
}

bool CrossingRoad::Navigation::OnScreenPause() {
	return currentScreen_->OnPause();
}

bool CrossingRoad::Navigation::OnScreenDestroy() {
	return currentScreen_->OnDestroy();
}

CrossingRoad::GameScreen* CrossingRoad::Navigation::currentScreen_ = nullptr;