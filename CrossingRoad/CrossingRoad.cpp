#include <iostream>
#include "GameEngine.h"
#include "Colors.h"
#include "Graphic.h"
#include "GameObject.h"

using namespace std;

int main() {
	GameEngine gameEngine = GameEngine();
	gameEngine.BuildConsole();

	Graphic::Sprite sprite = Graphic::Sprite("image.txt");
	GameObject object = GameObject(sprite);
	object.setPosition({ 10, 10 });	
	
	gameEngine.bindObjectToScreenBuffer(object);
	gameEngine.updateConsole();

	Graphic::gotoXY(10, 10);
	
	system("pause>nul");
	
	return 0;
}