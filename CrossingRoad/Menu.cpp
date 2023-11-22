#include "Menu.h"
#include "StreetMap.h"

bool Menu::OnCreate() {
	// set console color
	std::vector<int> colors = { 
		RGB(0, 0, 0),  // BLACK
		RGB(255, 255, 255),  // WHITE
		RGB(168, 201, 205),  // LIGHT GREEN
		RGB(214, 229, 230),  // LIGHT LIGHT GREEN
		RGB(128, 177, 177),  //  GREEN
		RGB(15, 47, 67),         //BORDER GREEN
		RGB(245, 211, 88), // YELLOW
		RGB(69, 56, 10), // DARK YELLOW
		RGB(187, 213, 245), // LIGHT BLUE
		RGB(118, 151, 201), // BLUE
		RGB(246, 135, 151), // PINK
		RGB(70, 70, 70), // DARK GRAY
		RGB(10,50,103),
		RGB(252,137,174), 
		RGB(253,218,133), 
		RGB(101,166,255), 
	};
	COLOR::SetConsoleColor(colors);

	// declaration
	std::vector<Widget::Button> buttons = {
		Widget::Button(
			game,
			"Play",
			[&]() {
				CrossingRoad::Navigation::To(new StreetMap(game));
			}
		),
		Widget::Button(
			game,
			"Setting",
			[&]() { 
				//CrossingRoad::Navigation::To(new Setting(game));
			}
		),
		Widget::Button(
			game,
			"About",
			[&]() { }
		),
	};

	menuWidget = MenuWidget(
		game,
		buttons,
		{ 100, 50 }
	);

	image = Image(DrawableRes::WhiteBG, Overlapped::LAND);
	chick = new GamePlayer(Player::CHICK, game);

	return true;
}

bool Menu::OnUpdate(float elapsedTime) {

	game->RenderSprite(image, { 0, 0 });
	// render menu widget
	menuWidget.Update(elapsedTime);

	return true;
}