#include "SettingScreen.h"
#include "StreetMap.h"
#include "MenuScreen.h"

bool SettingScreen::OnCreate() {
	// set console color
	std::vector<int> colors = {
		RGB(0, 0, 0),             // BLACK
		RGB(255, 255, 255),       // WHITE
		RGB(168, 201, 205),       // LIGHT GREEN
		RGB(214, 229, 230),       // LIGHT LIGHT GREEN
		RGB(128, 177, 177),       // GREEN
		RGB(15, 47, 67),          // BORDER GREEN
		RGB(245, 211, 88),        // YELLOW
		RGB(69, 56, 10),          // DARK YELLOW
		RGB(187, 213, 245),       // LIGHT BLUE
		RGB(118, 151, 201),       // BLUE
		RGB(246, 135, 151),        // PINK 
		RGB(10,50,103),
		RGB(252,137,174),
		RGB(253,218,133),
		RGB(101,166,255),
		RGB(153,152,154)
	};

	COLOR::SetConsoleColor(colors);

	// declaration

	std::vector<Widget::Button> buttons = {
		Widget::Button(
			game,
			"BACKGROUND MUSIC",
			[&]() {
				nullptr;
			}
		),
		Widget::Button(
			game,
			"EFFECT MUSIC",
			[&]() {
				nullptr;
			}
		),
		Widget::Button(
			game,
			"BACK",
			[&]() {
				CrossingRoad::Navigation::To(new MenuScreen(game));
			}
		),
	};

	settingWidget = SettingWidget(
		game,
		buttons,
		{ 150, 50 }
	);

	onToggle = Image();
	offToggle = Image();
	return true;
}

bool SettingScreen::OnUpdate(float elapsedTime) {
	settingWidget.Update(elapsedTime);
	return true;
}