#include "SettingScreen.h"
#include "MenuScreen.h"
#include "AboutScreen.h"

bool AboutScreen::OnCreate() {
	// set console color
	std::vector<int> colors = {
		//BAR
		RGB(0,0,0), //Black
		RGB(255,255,255), //White
		RGB(73,131,189), //Dark Blue
		RGB(137,184,212), //Blue
		RGB(189,213,229), //LightBlue
		RGB(168, 208, 230),  // LIGHT BLUE + bg

		//Button
		RGB(26,56,163),
		RGB(0,145,161),
		RGB(182,227,252)
	};

	COLOR::SetConsoleColor(colors);

	std::vector<Widget::Button> buttons = {
		Widget::Button(
			game,
			"BACK",
			[&]() {
				CrossingRoad::Navigation::To(new MenuScreen(game));
			}
		)
	};
	
	menuWidget = MenuWidget(
		game,
		buttons,
		{ 150, 50 }
	);

	// declaration
	return true;
}

bool AboutScreen::OnUpdate(float elapsedTime) {
	menuWidget.Update(elapsedTime);
	return true;
}
