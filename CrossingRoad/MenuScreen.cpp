#include "MenuScreen.h"
#include "SettingScreen.h"
#include "PlayMenuScreen.h"
#include "AboutScreen.h"
#include "LeaderBoard.h"

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
		RGB(126, 74, 76),          // DARK YELLOW
		RGB(187, 213, 245),       // LIGHT BLUE
		RGB(118, 151, 201),       // BLUE
		RGB(246, 135, 151),        // PINK 
		RGB(72, 78, 94), 
		RGB(127, 137, 173), 
		RGB(113, 215, 255),
		RGB(159, 204, 92),
		RGB(65, 39, 42)
	};

	// init widget
	InitWidget();
	game->SetConsoleColor(colors);

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

void MenuScreen::InitWidget()
{
	// background 
	bgImage = Image(DrawableRes::Background, Overlapped::BACKGROUND);

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
			"Character",
			[&]() {
				CrossingRoad::Navigation::To(new ChooseCharScreen(game));
			}
		),
		Widget::Button(
			game,
			"Leaderboard",
			[&]() {
				CrossingRoad::Navigation::To(new LeaderBoard(game));
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
		)
	};
	menuWidget = MenuWidget(
		game,
		buttons,
		{ 150, 60 }
	);

	//Crossing Road title
	// C R O S I N G A D
	std::vector<Graphic::Sprite> textCgif = {
		Graphic::Sprite(DrawableRes::menuTitleCharCwithShadow),
		Graphic::Sprite(DrawableRes::menuTitleCharCwithoutShadow)
	};
	std::vector<Graphic::Sprite> textRgif = {
		Graphic::Sprite(DrawableRes::menuTitleCharRwithShadow),
		Graphic::Sprite(DrawableRes::menuTitleCharRwithoutShadow)
	};
	std::vector<Graphic::Sprite> textOgif = {
		Graphic::Sprite(DrawableRes::menuTitleCharOwithShadow),
		Graphic::Sprite(DrawableRes::menuTitleCharOwithoutShadow)
	};
	std::vector<Graphic::Sprite> textSgif = {
		Graphic::Sprite(DrawableRes::menuTitleCharSwithShadow),
		Graphic::Sprite(DrawableRes::menuTitleCharSwithoutShadow)
	};
	std::vector<Graphic::Sprite> textIgif = {
		Graphic::Sprite(DrawableRes::menuTitleCharIwithShadow),
		Graphic::Sprite(DrawableRes::menuTitleCharIwithoutShadow)
	};
	std::vector<Graphic::Sprite> textNgif = {
		Graphic::Sprite(DrawableRes::menuTitleCharNwithShadow),
		Graphic::Sprite(DrawableRes::menuTitleCharNwithoutShadow)
	};
	std::vector<Graphic::Sprite> textGgif = {
		Graphic::Sprite(DrawableRes::menuTitleCharGwithShadow),
		Graphic::Sprite(DrawableRes::menuTitleCharGwithoutShadow)
	};
	std::vector<Graphic::Sprite> textAgif = {
		Graphic::Sprite(DrawableRes::menuTitleCharAwithShadow),
		Graphic::Sprite(DrawableRes::menuTitleCharAwithoutShadow)
	};
	std::vector<Graphic::Sprite> textDgif = {
		Graphic::Sprite(DrawableRes::menuTitleCharDwithShadow),
		Graphic::Sprite(DrawableRes::menuTitleCharDwithoutShadow)
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
}
