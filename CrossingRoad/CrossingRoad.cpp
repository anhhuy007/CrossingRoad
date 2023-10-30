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
		RGB(180, 180, 180), 
		RGB(70, 70, 70),
		RGB(117,75,61), 
		RGB(138,177,48), 
		RGB(98,129,36), 
		RGB(83,52,132),
		RGB(131,59,160), 
		RGB(89,101,115), 
		RGB(76,144,195), 
		RGB(123,140,154),
		RGB(54,34,86), 
		RGB(255, 192, 203), 
		RGB(183, 84, 84), 
		RGB(174,222,102)
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