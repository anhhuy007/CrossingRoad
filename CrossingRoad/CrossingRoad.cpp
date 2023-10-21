#include <iostream>
#include "GameEngine.h"
#include "Colors.h"
#include "Graphic.h"
#include "GameObject.h"
#include "Colors.h"

using namespace std;

int main() {
	GameEngine gameEngine = GameEngine();

	// set console color
	vector<int> colors = {
		COLOR::BLACK,
		COLOR::BLUE,
		COLOR::GREEN,
		COLOR::YELLOW,
		COLOR::RED,
		COLOR::PURPLE,
		COLOR::BROWN,
		COLOR::LIGHT_GRAY,
		COLOR::ORANGE,
		COLOR::LIGHT_BLUE,
		COLOR::LIGHT_GREEN,
		COLOR::LIGHT_YELLOW,
		COLOR::LIGHT_RED,
		COLOR::PINK,
		COLOR::LIGHT_BROWN,
		COLOR::WHITE
	};

	COLOR::SetConsoleColor(colors);
	
	gameEngine.BuildConsole();

	Graphic::Sprite sprite = Graphic::Sprite("image.sprite");
	GameObject object = GameObject(sprite);
	object.setPosition({ 10, 10 });	
	
	gameEngine.bindObjectToScreenBuffer(object);
	gameEngine.updateConsole();

	Graphic::gotoXY(100, 20);
	
	system("pause>nul");
	
	return 0;
}