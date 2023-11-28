#include "TestScreen.h"

bool TestScreen::OnCreate() {
	// set console color
	std::vector<int> colors = {
		RGB(0, 0, 0),
		RGB(255, 255, 255),
		RGB(174, 222, 102),
		RGB(159, 204, 92),
		RGB(110, 184, 46),
		RGB(12, 67, 57),
		RGB(127, 137, 173),
		RGB(96, 109, 138),
		RGB(72, 78, 94),
		RGB(113, 215, 255),
		RGB(126, 74, 76),
		RGB(255, 112, 51),
		RGB(65, 39, 42),
		RGB(255, 59, 69),
		RGB(176, 40, 49),
		RGB(77, 18, 30)
	};

	COLOR::SetConsoleColor(colors);

	bgImage = Image(DrawableRes::WhiteBG, Overlapped::BACKGROUND);

	std::vector<Widget::Button> buttons = {
		Widget::Button(
			game,
			"Exit",
			[](){}
		),
		Widget::Button(
			game,
			"Save game",
			[](){}
		),
		Widget::Button(
			game,
			"Continue",
			[](){}
		),
	};

	dialog = Widget::Dialog(
		game,
		"Choose your option",
		buttons, 
		{ 50, 50 },
		100,
		100
	);

	return true;
}

bool TestScreen::OnUpdate(float elapsedTime) {
	game->RenderSprite(bgImage, { 0, 0 });

	dialog.Update(elapsedTime);
	dialog.Render();

	return true;
}