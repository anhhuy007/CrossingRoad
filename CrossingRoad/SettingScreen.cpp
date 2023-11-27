#include "SettingScreen.h"
#include "MenuScreen.h"

bool SettingScreen::OnCreate() {

	std::vector<Graphic::Sprite> textSgif = {
		Graphic::Sprite("Screen\\settingScreen\\title\\withShadow\\S.sprite"),
		Graphic::Sprite("Screen\\settingScreen\\title\\withoutShadow\\S.sprite"),
	};
	std::vector<Graphic::Sprite> textEgif = {
		Graphic::Sprite("Screen\\settingScreen\\title\\withShadow\\E.sprite"),
		Graphic::Sprite("Screen\\settingScreen\\title\\withoutShadow\\E.sprite")
	};
	std::vector<Graphic::Sprite> textTgif = {
		Graphic::Sprite("Screen\\settingScreen\\title\\withShadow\\T.sprite"),
		Graphic::Sprite("Screen\\settingScreen\\title\\withoutShadow\\T.sprite")
	};
	std::vector<Graphic::Sprite> textIgif = {
		Graphic::Sprite("Screen\\settingScreen\\title\\withShadow\\I.sprite"),
		Graphic::Sprite("Screen\\settingScreen\\title\\withoutShadow\\I.sprite")
	};
	std::vector<Graphic::Sprite> textNgif = {
		Graphic::Sprite("Screen\\settingScreen\\title\\withShadow\\N.sprite"),
		Graphic::Sprite("Screen\\settingScreen\\title\\withoutShadow\\N.sprite")
	};
	std::vector<Graphic::Sprite> textGgif = {
		Graphic::Sprite("Screen\\settingScreen\\title\\withShadow\\G.sprite"),
		Graphic::Sprite("Screen\\settingScreen\\title\\withoutShadow\\G.sprite")
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
		),
		Widget::Button(
			game,
			"CHANGE CHARACTER",
			[]() {}
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

	image = Image(DrawableRes::LightBlueBG, Overlapped::BACKGROUND);
	short top_border = 10, left = 130, space = 28;
	S = Animation(game, textSgif, { left, top_border }, 400); left += space;
	E = Animation(game, textEgif, { left, top_border }, 400); left += space;
	T1 = Animation(game, textTgif, { left, top_border }, 400); left += space;
	T2 = Animation(game, textTgif, { left, top_border }, 400); left += space;
	I = Animation(game, textIgif, { left, top_border }, 400); left += space;
	N = Animation(game, textNgif, { left, top_border }, 400); left += space;
	G = Animation(game, textGgif, { left, top_border }, 400); left += space;

	COLOR::SetConsoleColor(colors);

	return true;
}

bool SettingScreen::OnUpdate(float elapsedTime) {
	game->RenderSprite(image, { 0,0 });
	S.OnPlay(elapsedTime);
	E.OnPlay(elapsedTime);
	T1.OnPlay(elapsedTime);
	T2.OnPlay(elapsedTime);
	I.OnPlay(elapsedTime);
	N.OnPlay(elapsedTime);
	G.OnPlay(elapsedTime);

	settingWidget.Update(elapsedTime);
	return true;
}

