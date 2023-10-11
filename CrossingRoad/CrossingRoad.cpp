#include <iostream>
#include "GameEngine.h"
#include "Colors.h"
#include "Graphic.h"
#include "GameObject.h"

using namespace std;

int main() {
	GameEngine gameEngine;

	gameEngine.BuildConsole();

	SMALL_RECT box = { 20, 20, 50, 50 };

	string colors[10] = {
		"#f6e807",
		"#f9ec1e",
		"#f9ee37",
		"#faf050",
		"#fbf269",
		"#fbf482",
		"#fcf69a",
		"#afa838",
		"#969030",
		"#c6bf4d"
	};

	GameObject object = GameObject(10, 10);
	for (int i = 0; i < 10; i++) {
		string color = colors[i];
		for (int j = 0; j < 10; j++) {
			object.setPixel(
				{ short(i), short(j) },
				colors[i]
			);
		}
	}
	Graphic::displayObject(
		object,
		box,
		Alignment(ALIGNMENT_GRAVITY::BOTTOM_LEFT, 0, 0, 0, 0, box)
	);

	system("pause>nul");
	
	return 0;
}