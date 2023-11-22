#include "CrossingRoad.h"
#include "GameMap.h"
#include "StreetMap.h"
#include "MenuScreen.h"

void CrossingRoad::Init() {
	// ----- Init game -----
	GameEngine::BuildConsole();	
	Navigation::To(new MenuScreen(this));
}

bool CrossingRoad::GameCreate() {
	// ----- Create new game -----
	GameEngine::BuildConsole();

	Navigation::To(new StreetMap(this));

	return true;
}

bool CrossingRoad::GameUpdate(float elapsedTime) {
	// ----- Game pause -----
	if (inputHandle->keyState_[Keyboard::ESCAPE_KEY].isPressed) {
		return Navigation::OnScreenDestroy();
	}

	// ------ Game Update -----
	return Navigation::OnScreenUpdate(elapsedTime);
}

void CrossingRoad::Navigation::To(std::string route) {
	// do some navigation
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