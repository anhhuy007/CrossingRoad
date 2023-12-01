#include "PlayMenuScreen.h"
#include "MenuScreen.h"
#include "ClassicMap.h"
#include "WinterMap.h"

bool PlayMenuScreen::OnCreate() {
	InitWidget();
	return true;
}

bool PlayMenuScreen::OnUpdate(float elapsedTime) {
	// if player press ESC, then back to menu screen
	if (game->inputHandle->keyState_[Keyboard::ESCAPE_KEY].isPressed) {
		CrossingRoad::Navigation::To(new MenuScreen(game));
	}

	game->RenderSprite(bgImage, { 0, 0 });
	playMenuWidget.Update(elapsedTime);

	return true;
}

void PlayMenuScreen::InitWidget()
{
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
			"ENDLESS MODE",
			[&]() {
				OnEndlessModeClicked();
			}
		),
		Widget::Button(
			game,
			"LEVEL MODE",
			[&]() {
				OnLevelModeClicked();
			}
		),
		Widget::Button(
			game,
			"LOAD GAME",
			[&]() {
				OnLoadGameClicked();
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

	playMenuWidget = MenuWidget(
		game,
		buttons,
		{ 150, 50 }
	);

	bgImage = Image(DrawableRes::WhiteBG, Overlapped::BACKGROUND);
}

void PlayMenuScreen::OnLevelModeClicked()
{
	int random = rand() % 2;
	if (random == 0) {
		CrossingRoad::Navigation::To(new ClassicMap(game, GameMode::LEVEL_MODE));
	}
	else {
		CrossingRoad::Navigation::To(new WinterMap(game, GameMode::LEVEL_MODE));
	}
}

void PlayMenuScreen::OnEndlessModeClicked()
{
	int random = rand() % 2;
	if (random == 0) {
		CrossingRoad::Navigation::To(new ClassicMap(game, GameMode::ENDLESS_MODE));
	}
	else {
		CrossingRoad::Navigation::To(new WinterMap(game, GameMode::ENDLESS_MODE));
	}
}

void PlayMenuScreen::OnLoadGameClicked()
{
}
