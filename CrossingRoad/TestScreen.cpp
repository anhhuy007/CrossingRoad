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
	game->SetConsoleColor(colors);

	// display screen to ask player to enter game name
	bgImage = Image(DrawableRes::Background, Overlapped::BACKGROUND);
	text = Widget::Text(
		game,
		"This is a normal text, with special . character <for testing>: ",
		{ 50, 100 },
		200, 50,
		TextFont::NORMAL
	);

	return true;
}

bool TestScreen::OnUpdate(float elapsedTime) {
	game->RenderSprite(bgImage, { 0, 0 });
	text.Render();

	return true;
}