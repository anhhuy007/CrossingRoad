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


	currentChar = rand()%3 +1  ; //add navigation code instead
	if (currentChar == 1) {
		COLOR::SetConsoleColor(colors1);
	}
	else if (currentChar == 2) {
		COLOR::SetConsoleColor(colors2);
	}
	else if (currentChar == 3) {
		COLOR::SetConsoleColor(colors3);
	}

	return true;
}

bool ChooseCharScreen::OnUpdate(float elapsedTime)
{
	

	if (currentChar == 1)
		{
			game->RenderSprite(char1, { 0,0 });
		}
		else if (currentChar == 2)
		{
			game->RenderSprite(char2, { 0,0 });
		}
		else if (currentChar == 3)
		{
			game->RenderSprite(char3, { 0,0 });
		}

	return true;
}