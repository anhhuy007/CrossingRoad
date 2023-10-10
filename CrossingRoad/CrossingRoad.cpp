#include <iostream>
#include "GameEngine.h"
#include "Colors.h"

using namespace std;

int main() {
	GameEngine gameEngine;

	gameEngine.BuildConsole();

	SMALL_RECT box = { 20, 20, 50, 50 };
	
	gameEngine.displayObject(
		gameEngine.createWrappedObject(10, 10),
		10,
		10,
		Alignment(ALIGNMENT_GRAVITY::CENTRALLY_ALIGNED, 0, 0, 0, 0, box)
	);

	system("pause>nul");
	
	return 0;
}