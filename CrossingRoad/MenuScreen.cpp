#include "MenuScreen.h"
#include "ClassicMap.h"
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

	// background 
	bgImage = Image(DrawableRes::WhiteBG, Overlapped::BACKGROUND);

	// Menu button function
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

	//Crossing Road title

	std::vector<Graphic::Sprite> textCgif = {
		Graphic::Sprite("Screen\\menuScreen\\title\\withShadow\\withShadowC.sprite"),
		Graphic::Sprite("Screen\\menuScreen\\title\\withoutShadow\\withoutShadowC.sprite")
	};
	std::vector<Graphic::Sprite> textRgif = {
		Graphic::Sprite("Screen\\menuScreen\\title\\withShadow\\withShadowR.sprite"),
		Graphic::Sprite("Screen\\menuScreen\\title\\withoutShadow\\withoutShadowR.sprite")
	};
	std::vector<Graphic::Sprite> textOgif = {
		Graphic::Sprite("Screen\\menuScreen\\title\\withShadow\\withShadowO.sprite"),
		Graphic::Sprite("Screen\\menuScreen\\title\\withoutShadow\\withoutShadowO.sprite")
	};
	std::vector<Graphic::Sprite> textSgif = {
		Graphic::Sprite("Screen\\menuScreen\\title\\withShadow\\withShadowS.sprite"),
		Graphic::Sprite("Screen\\menuScreen\\title\\withoutShadow\\withoutShadowS.sprite")
	};
	std::vector<Graphic::Sprite> textIgif = {
		Graphic::Sprite("Screen\\menuScreen\\title\\withShadow\\withShadowI.sprite"),
		Graphic::Sprite("Screen\\menuScreen\\title\\withoutShadow\\withoutShadowI.sprite")
	};
	std::vector<Graphic::Sprite> textNgif = {
		Graphic::Sprite("Screen\\menuScreen\\title\\withShadow\\withShadowN.sprite"),
		Graphic::Sprite("Screen\\menuScreen\\title\\withoutShadow\\withoutShadowN.sprite")
	};
	std::vector<Graphic::Sprite> textGgif = {
		Graphic::Sprite("Screen\\menuScreen\\title\\withShadow\\withShadowG.sprite"),
		Graphic::Sprite("Screen\\menuScreen\\title\\withoutShadow\\withoutShadowG.sprite")
	};
	std::vector<Graphic::Sprite> textDgif = {
		Graphic::Sprite("Screen\\menuScreen\\title\\withShadow\\withShadowD.sprite"),
		Graphic::Sprite("Screen\\menuScreen\\title\\withoutShadow\\withoutShadowD.sprite")
	};
	std::vector<Graphic::Sprite> textAgif = {
		Graphic::Sprite("Screen\\menuScreen\\title\\withShadow\\withShadowA.sprite"),
		Graphic::Sprite("Screen\\menuScreen\\title\\withoutShadow\\withoutShadowA.sprite"),
	};

	short top_border = 20, left = 50, space = 28;
	C = Animation(game, textCgif, { left, top_border }, 400); left += space;
	R1 = Animation(game, textRgif, { left, top_border }, 400); left += space;
	O1 = Animation(game, textOgif, { left, top_border }, 400); left += space;
	S1 = Animation(game, textSgif, { left, top_border }, 400); left += space;
	S2 = Animation(game, textSgif, { left, top_border }, 400); left += space;
	I = Animation(game, textIgif, { left, top_border }, 400); left += space;
	N = Animation(game, textNgif, { left, top_border }, 400); left += space;
	G = Animation(game, textGgif, { left, top_border }, 400); left += (space + 15);

	R2 = Animation(game, textRgif, { left, top_border }, 400); left += space;
	O2 = Animation(game, textOgif, { left, top_border }, 400); left += space;
	A = Animation(game, textAgif, { left, top_border }, 400); left += space;
	D = Animation(game, textDgif, { left, top_border }, 400);

	game->BuildConsole();
	COLOR::SetConsoleColor(colors);

	game->sound->playBackgroundSound(int(Sound::Background::BACKGROUND_MUSIC));
	return true;
}

bool MenuScreen::OnUpdate(float elapsedTime) {
	game->RenderSprite(bgImage, { 0, 0 });
	menuWidget.Update(elapsedTime);

	C.OnPlay(elapsedTime);
	R1.OnPlay(elapsedTime);
	R2.OnPlay(elapsedTime);
	O1.OnPlay(elapsedTime);
	O2.OnPlay(elapsedTime);
	S1.OnPlay(elapsedTime);
	S2.OnPlay(elapsedTime);
	I.OnPlay(elapsedTime);
	N.OnPlay(elapsedTime);
	G.OnPlay(elapsedTime);
	A.OnPlay(elapsedTime);
	D.OnPlay(elapsedTime);

	return true;
}