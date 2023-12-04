#include "TestScreen.h"

bool TestScreen::OnCreate() {
	// set console color
	std::vector<int> colors = {
		RGB(0, 0, 0),			// black
		RGB(255, 255, 255),		// white
		RGB(174, 222, 102),		// green
		RGB(159, 204, 92),		// green
		RGB(110, 184, 46),		// green
		RGB(12, 67, 57),		// green
		RGB(127, 137, 173),		// blue
		RGB(96, 109, 138),		// blue	
		RGB(72, 78, 94),		// blue
		RGB(113, 215, 255),		// blue	
		RGB(126, 74, 76),		// red
		RGB(255, 112, 51),		// orange	
		RGB(65, 39, 42),		// brown
		RGB(255, 59, 69),		// red
		RGB(176, 40, 49),		// red
		RGB(77, 18, 30)			// red
	};
	COLOR::SetConsoleColor(colors);

	// display screen to ask player to enter game name
	std::string gameName;
	Image bg = Image(DrawableRes::WhiteBG, Overlapped::BACKGROUND);
	Widget::Text title = Widget::Text(
		game,
		"Enter game name",
		{ 140, 70 },
		100, 30,
		TextFont::NORMAL,
		3 // green 
	);
	Widget::Text inputText = Widget::Text(
		game,
		"firstgame",
		{ 230, 70 },
		200, 30,
		TextFont::NORMAL
	);
	Widget::Text rule = Widget::Text(
		game,
		"Game name must be less than 20 characters and contain no special characters",
		{ 140, 100 },
		200, 30,
		TextFont::NORMAL,
		3 // blue
	);

	Widget::Text note = Widget::Text(
		game,
		"Press ENTER to save game or ESC to exit",
		{ 140, 120 },
		200, 40,
		TextFont::NORMAL,
		3 // blue
	);

	// get game name from player
	while (true) {
		game->inputHandle = InputHandle::GetKeyBoardState();
		if (game->inputHandle->keyState_[Keyboard::ENTER_KEY].isPressed) {
			if (gameName.size() > 0) {
				return true;
			}
		}
		else if (game->inputHandle->keyState_[Keyboard::ESCAPE_KEY].isPressed) {
			return true;
		}

		// get input from player
		for (int i = 0; i < keyNumber; i++) {
			if (game->inputHandle->keyState_[i].isPressed) {
				if (i == Keyboard::BACKSPACE_KEY) {
					if (gameName.size() > 0) {
						gameName.pop_back();
					}
				}
				else if (i == Keyboard::ENTER_KEY) {
					if (gameName.size() > 0) {
						return true;
					}
				}
				else if ((i >= Keyboard::A_KEY && i <= Keyboard::Z_KEY) ||
						(i >= Keyboard::a_KEY && i <= Keyboard::z_KEY) ||
						(i >= Keyboard::NUM_0_KEY && i <= Keyboard::NUM_9_KEY) ||
						 i == Keyboard::SPACE_KEY
					) {
					if (gameName.size() < 20) {
						gameName.push_back(i);
					}
				}
			}
		}

		// update input text
		game->ClearConsole();
		game->RenderSprite(bg, { 0, 0 });
		inputText.UpdateText(gameName);
		inputText.Render();
		title.Render();
		rule.Render();
		note.Render();
		game->UpdateConsole();
	}

	return true;
}

bool TestScreen::OnUpdate(float elapsedTime) {

	return true;
}