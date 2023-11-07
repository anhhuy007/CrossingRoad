#include <iostream>
#include "CrossingRoad.h"

int main() {
	CrossingRoad game;
	srand(time(NULL));

	game.Init();
	game.Start();

	return 0;
}