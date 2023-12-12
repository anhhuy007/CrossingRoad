#include "AboutScreen.h"
#include "MenuScreen.h"


bool AboutScreen::OnCreate() {
	// N H O M 1
	std::vector<Graphic::Sprite> textNgif = {
		Graphic::Sprite(DrawableRes::splashTitleCharNwithShadow),
		Graphic::Sprite(DrawableRes::splashTitleCharNwithoutShadow)
	};
	std::vector<Graphic::Sprite> textHgif = {
		Graphic::Sprite(DrawableRes::splashTitleCharHwithShadow),
		Graphic::Sprite(DrawableRes::splashTitleCharHwithoutShadow)
	};
	std::vector<Graphic::Sprite> textOgif = {
		Graphic::Sprite(DrawableRes::splashTitleCharOwithShadow),
		Graphic::Sprite(DrawableRes::splashTitleCharOwithoutShadow)
	};
	std::vector<Graphic::Sprite> textMgif = {
		Graphic::Sprite(DrawableRes::splashTitleCharMwithShadow),
		Graphic::Sprite(DrawableRes::splashTitleCharMwithoutShadow)
	};
	std::vector<Graphic::Sprite> textNum1gif = {
		Graphic::Sprite(DrawableRes::splashTitleChar1withShadow),
		Graphic::Sprite(DrawableRes::splashTitleChar1withoutShadow)
	};
	std::vector<Graphic::Sprite> textAcutegif = {
		Graphic::Sprite(DrawableRes::splashTitleCharACUTEwithShadow),
		Graphic::Sprite(DrawableRes::splashTitleCharACUTEwithoutShadow)
	};

    // set console color
	std::vector<int> colors = {
		RGB(0, 0, 0),
	RGB(255, 255, 255),
	RGB(168, 201, 205),
	RGB(214, 229, 230),
	RGB(128, 177, 177),
	RGB(15, 47, 67),
	RGB(0, 186, 255),
	RGB(105, 206, 236),
	RGB(159, 250, 222),
	RGB(72, 78, 94),
	RGB(235, 90, 87),
	RGB(96, 109, 138),
	RGB(72, 78, 94),
	RGB(113, 215, 255),
	RGB(126, 74, 76),
	RGB(255, 112, 51)
	};

	game->SetConsoleColor(colors);

	std::vector<Image> about;
	for (int i = 1; i <= 5; i++)
	{
		std::string path = DrawableRes::aboutFolder + "frame" + std::to_string(i) + ".sprite";
		about.push_back(Image(path));
	}

	esc = Image(DrawableRes::escText);

	aboutAnimation = Animation(game, about, { 0, 0 }, 2500);

	//declare
	N = Animation(game, textNgif, { 150, 47 }, 400);
	H = Animation(game, textHgif, { 180, 47 }, 400);
	O = Animation(game, textOgif, { 210, 47 }, 400);
	M = Animation(game, textMgif, { 240, 47 }, 400);
	num1a = Animation(game, textNum1gif, { 270, 47 }, 400);
	num1b = Animation(game, textNum1gif, { 290, 47 }, 400);
	acute = Animation(game, textAcutegif, { 210 + 7, 47 - 10 }, 400);

	return true;	
}

bool AboutScreen::OnUpdate(float elapsedTime) {
	// if player press ESC, then back to menu screen
	if (game->inputHandle->keyState_[Keyboard::ESCAPE_KEY].isPressed) {
		CrossingRoad::Navigation::To(new MenuScreen(game));
	}

	aboutAnimation.OnPlay(elapsedTime);
	N.OnPlay(elapsedTime);
	H.OnPlay(elapsedTime);
	O.OnPlay(elapsedTime);
	M.OnPlay(elapsedTime);
	num1a.OnPlay(elapsedTime);
	num1b.OnPlay(elapsedTime);
	acute.OnPlay(elapsedTime);

	game->RenderSprite(esc, { 132, 207 });

    return true;
}
