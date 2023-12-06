#include "SettingScreen.h"
#include "MenuScreen.h"

bool SettingScreen::OnCreate() {

	// S E T I N G
	std::vector<Graphic::Sprite> textSgif = {
	Graphic::Sprite(DrawableRes::settingTitleCharSwithShadow),
	Graphic::Sprite(DrawableRes::settingTitleCharSwithoutShadow),
	};
	std::vector<Graphic::Sprite> textEgif = {
	Graphic::Sprite(DrawableRes::settingTitleCharEwithShadow),
	Graphic::Sprite(DrawableRes::settingTitleCharEwithoutShadow),
	};
	std::vector<Graphic::Sprite> textTgif = {
	Graphic::Sprite(DrawableRes::settingTitleCharTwithShadow),
	Graphic::Sprite(DrawableRes::settingTitleCharTwithoutShadow),
	};
	std::vector<Graphic::Sprite> textIgif = {
		Graphic::Sprite(DrawableRes::settingTitleCharIwithShadow),
		Graphic::Sprite(DrawableRes::settingTitleCharIwithoutShadow),
	};
	std::vector<Graphic::Sprite> textNgif = {
		Graphic::Sprite(DrawableRes::settingTitleCharNwithShadow),
		Graphic::Sprite(DrawableRes::settingTitleCharNwithoutShadow),
	};
	std::vector<Graphic::Sprite> textGgif = {
		Graphic::Sprite(DrawableRes::settingTitleCharGwithShadow),
		Graphic::Sprite(DrawableRes::settingTitleCharGwithoutShadow),
	};

	// set console color
	std::vector<int> colors = {
	
	//BAR
	RGB(0,0,0), //Black
	RGB(255,255,255), //White

	//bar button
	RGB(73,131,189), //Dark Blue
	RGB(137,184,212), //Blue
	RGB(189,213,229), //Light light Blue for button border
	RGB(168, 208, 230),  // LIGHT BLUE + bg

	//Button

	RGB(26,56,163),
	RGB(0,145,161),
	RGB(182,227,252),

	//text
	RGB(15,47,67),
	};

	// declaration

	std::vector<Widget::Button> buttons = {
		Widget::Button(
			game,
			"BACKGROUND MUSIC",
			[]() {}
		),
		Widget::Button(
			game,
			"EFFECT MUSIC",
			[]() {}
		)
	};

	settingWidget = SettingWidget(
		game,
		buttons,
		{ 150, 50 }
	);

	bgImage = Image(DrawableRes::LightBlueBG, Overlapped::BACKGROUND);
	short top_border = 10, left = 130, space = 28;
	S = Animation(game, textSgif, { left, top_border }, 400); left += space;
	E = Animation(game, textEgif, { left, top_border }, 400); left += space;
	T1 = Animation(game, textTgif, { left, top_border }, 400); left += space;
	T2 = Animation(game, textTgif, { left, top_border }, 400); left += space;
	I = Animation(game, textIgif, { left, top_border }, 400); left += space;
	N = Animation(game, textNgif, { left, top_border }, 400); left += space;
	G = Animation(game, textGgif, { left, top_border }, 400); left += space;

	music = Widget::Text(game, "MUSIC", { 111,73 }, 25, 34, TextFont::NORMAL);
	sfx = Widget::Text(game, "SFX", { 115,104 }, 15, 34, TextFont::NORMAL);

	game->SetConsoleColor(colors);

	return true;
}

bool SettingScreen::OnUpdate(float elapsedTime) {
	// if player press ESC, then back to menu screen
	if (game->inputHandle->keyState_[Keyboard::ESCAPE_KEY].isPressed) {
		CrossingRoad::Navigation::To(new MenuScreen(game));
	}

	game->RenderSprite(bgImage, { 0,0 });

	S.OnPlay(elapsedTime);
	E.OnPlay(elapsedTime);
	T1.OnPlay(elapsedTime);
	T2.OnPlay(elapsedTime);
	I.OnPlay(elapsedTime);
	N.OnPlay(elapsedTime);
	G.OnPlay(elapsedTime);

	music.Render();
	sfx.Render();
	back.Render();
	settingWidget.Update(elapsedTime);

	return true;
}

