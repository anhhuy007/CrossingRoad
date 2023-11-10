#include "CrossingRoad.h"
#include "GameMap.h"
#include "StreetMap.h"

void CrossingRoad::Init() {
	// ----- Init game -----
	// Init game engine
	GameEngine::BuildConsole();

	vector<int> colors = {
		RGB(0, 0, 0), 
		RGB(255, 255, 255), 
		RGB(174, 222, 102), 
		RGB(159, 204, 92),
		RGB(110, 184, 46), 
		RGB(12, 67, 57), 
		RGB(127, 137, 173),  
		RGB(96, 109, 138),
		RGB(72, 78, 94), 
		RGB(113, 215, 255), 
		RGB(126, 74, 76),
		RGB(255, 112, 51),
		RGB(65, 39, 42), 
		RGB(255, 59, 69), 
		RGB(176, 40, 49), 
		RGB(77, 18, 30)
	};
	
	COLOR::SetConsoleColor(colors);

	// Init game state
	this->gameState = new StreetMap(this);
	this->SetState(this->gameState);
}

bool CrossingRoad::GameCreate() {
	// ----- Create new game -----
	SetState(new StreetMap(this));
	
	return true;
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