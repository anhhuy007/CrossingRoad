#include "CrossingRoad.h"

void CrossingRoad::Init() {
	// ----- Init game -----
	// Init game engine
	GameEngine::BuildConsole();

	// Init game state
	this->gameState = new GameState(this);
	this->SetState(this->gameState);
}

bool CrossingRoad::GameUpdate(float elapsedTime) {
	// ----- Update game -----
	if (inputHandle.arrKeyState[Keyboard::ESCAPE_KEY].isPressed) return false;

	// game loop
	if (gameState != nullptr) {
		return gameState->Update(elapsedTime);
	}

	return true;
}