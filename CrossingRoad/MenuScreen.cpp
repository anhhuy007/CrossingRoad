#include "MenuScreen.h"
#include "StreetMap.h"
#include "SettingScreen.h"
#include "PlayMenuScreen.h"
#include "AboutScreen.h"

bool MenuScreen::OnCreate() {
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
			"Play",
			[&]() {
				CrossingRoad::Navigation::To(new PlayMenuScreen(game));
			}
		),
		Widget::Button(
			game,
			"Leaderboard",
			[&]() {
				//CrossingRoad::Navigation::To(new LeaderboardScreen(game));
			}
		),
		Widget::Button(
			game,
			"Setting",
			[&]() {
				CrossingRoad::Navigation::To(new SettingScreen(game));
			}
		),
		Widget::Button(
			game,
			"About",
			[&]() {
				CrossingRoad::Navigation::To(new AboutScreen(game));
			}
		),
		Widget::Button(
			game,
			"Exit",
			[&]() {
			}
		)
	};

	menuWidget = MenuWidget(
		game,
		buttons,
		{ 150, 60 }
	);
	image = Image(DrawableRes::WhiteBG, Overlapped::BACKGROUND);

	//Play background Sound
	Sound::playBackgroundSound(game->soundSetting, -1, int(Sound::Background::BACKGROUND_MUSIC));
	return true;
}

bool MenuScreen::OnUpdate(float elapsedTime) {
	/*text.Render();
	button.Render();*/
	game->RenderSprite(image, { 0, 0 });
	//meow.OnPlay(elapsedTime);

	menuWidget.Update(elapsedTime);

	return true;
}