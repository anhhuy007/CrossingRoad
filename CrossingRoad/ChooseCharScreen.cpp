#include "ChooseCharScreen.h"

bool ChooseCharScreen::OnCreate()
{
	char1 = Image(DrawableRes::chooseChar1);
	char2 = Image(DrawableRes::chooseChar2);
	char3 = Image(DrawableRes::chooseChar3);
	
	//-----------------------------COLOR SAVEGAME---------------------------
	colors1 = {
		RGB(255, 255, 255),  // WHITE
		RGB(235, 219, 229),
		RGB(0, 0, 0),  // BLACK
		RGB(159, 250, 222),
		RGB(0, 186, 255),
		RGB(0, 105, 236),
		RGB(250, 222, 159),
		RGB(100, 58, 58),
		RGB(255, 151, 112),
		RGB(226, 86, 84),
		RGB(171, 171, 171),
		RGB(107, 107, 107),
		RGB(61, 61, 61),
		RGB(174, 222, 102),
		RGB(110, 184, 46),
		RGB(65, 39, 42)
	};
	colors2 = {
	RGB(255, 255, 255),    // WHITE
	RGB(235, 219, 229),
	RGB(0, 0, 0),          // BLACK
	RGB(159, 250, 222),
	RGB(0, 186, 255),
	RGB(0, 105, 236),
	RGB(250, 222, 159),
	RGB(100, 58, 58),
	RGB(255, 151, 112),
	RGB(226, 86, 84),
	RGB(171, 171, 171),
	RGB(107, 107, 107),
	RGB(61, 61, 61),
	RGB(255, 111, 166),
	RGB(229, 62, 118),
	RGB(72, 78, 92)
	};
	colors3 = {
	RGB(255, 255, 255),    // WHITE
	RGB(235, 219, 229),
	RGB(0, 0, 0),          // BLACK
	RGB(159, 250, 222),
	RGB(0, 186, 255),
	RGB(0, 105, 236),
	RGB(250, 222, 159),
	RGB(100, 58, 58),
	RGB(255, 151, 112),
	RGB(226, 86, 84),
	RGB(171, 171, 171),
	RGB(107, 107, 107),
	RGB(61, 61, 61),
	RGB(127, 137, 173),
	RGB(96, 109, 138),
	RGB(72, 78, 92)
	};

	currentChar =  (int)game->userOption.player ; //add navigation code instead
	return true;
}

bool ChooseCharScreen::OnUpdate(float elapsedTime)
{
	// handle key pressed
	if (game->inputHandle->keyState_[Keyboard::ESCAPE_KEY].isPressed) {
		CrossingRoad::Navigation::To(new MenuScreen(game));
		return true;
	}
	else if (game->inputHandle->keyState_[Keyboard::LEFT_KEY].isPressed) {
		currentChar--;
		if (currentChar < 0) currentChar = 2;
	}
	else if (game->inputHandle->keyState_[Keyboard::RIGHT_KEY].isPressed) {
		currentChar++;
		if (currentChar > 2) currentChar = 0;
	}
	else if (game->inputHandle->keyState_[Keyboard::ENTER_KEY].isPressed) {
		game->userOption.player = Player { currentChar };
		CrossingRoad::Navigation::To(new MenuScreen(game));
		return true;
	}

	

	if (currentChar == 0)
	{
		game->SetConsoleColor(colors1);
		game->RenderSprite(char1, { 0,0 });
	}
	else if (currentChar == 1)
	{
		game->SetConsoleColor(colors2);
		game->RenderSprite(char2, { 0,0 });
	}
	else if (currentChar == 2)
	{
		game->SetConsoleColor(colors3);
		game->RenderSprite(char3, { 0,0 });
	}

	return true;
}