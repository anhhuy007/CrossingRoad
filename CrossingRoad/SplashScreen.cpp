#include "SplashScreen.h"

bool SplashScreen::OnCreate()
{
	std::string animationPath = "Screen\\splashScreen\\animation\\";
	std::vector<Graphic::Sprite> chickenGif;
	for (int i = 1; i <= 9 ; i++)
	{
		chickenGif.push_back(Graphic::Sprite(animationPath + "chickenGif\\frame" + std::to_string(i) + ".sprite"));
	}
	std::vector<Graphic::Sprite> bubblesGif;
	for (int i = 1; i <= 5; i++)
	{
		bubblesGif.push_back(Graphic::Sprite(animationPath + "bubblesGif\\frame" + std::to_string(i) + ".sprite"));
	}

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



	//set color
	std::vector<int> colors = {
		RGB(0, 0, 0),  // BLACK
		RGB(255, 255, 255),  // WHITE
		RGB(168, 201, 205),  // LIGHT BLUE
		RGB(214, 229, 230),  // LIGHT LIGHT GREEN
		RGB(128, 177, 177),  //  GREEN
		RGB(15, 47, 67),         //BORDER GREEN

		//chicken
		RGB(245, 228, 238),  // WHITE SHADOW
		RGB(229, 60, 117),  // RED HAIR
		RGB(255, 110, 165),  // LIGHT RED HAIR
		RGB(235, 90, 87),  // ORANGE
		RGB(255, 150, 111),  // LIGHT ORANGE
		//bg
		RGB(105, 206, 236),  // BLUE BG
		RGB(94, 193, 225),  // BG WITH SHADOW
		//13/16


			RGB(127, 137, 173),
			RGB(96, 109, 138),
			RGB(72, 78, 94),
	};
	game->SetConsoleColor(colors);

	//declare
	bg = Image("Screen\\splashScreen\\img\\bgSplashScreen.sprite");
	chicken = Animation(game, chickenGif, { 170, 70 }, 100);
	N = Animation(game, textNgif, { 150, 17 }, 400);
	H = Animation(game, textHgif, { 180, 17 }, 400);
	O = Animation(game, textOgif, { 210, 17 }, 400);
	M = Animation(game, textMgif, { 240, 17 }, 400);
	num1a = Animation(game, textNum1gif, { 270, 17 }, 400);
	num1b = Animation(game, textNum1gif, { 290, 17 }, 400);
	acute = Animation(game, textAcutegif, { 210 + 7, 17 - 10 }, 400);
	bubbles = Animation(game, bubblesGif, { 0, 0 }, 200);

	return true;
}

bool SplashScreen::OnUpdate(float elapsedTime)
{
	time += elapsedTime;

	if (time > 5000) {
		CrossingRoad::Navigation::To(new MenuScreen(game));
		return true;

		time = 0;
	}

	game->RenderSprite(bg, { 0, 0 });
	bubbles.OnPlay(elapsedTime);
	N.OnPlay(elapsedTime);
	H.OnPlay(elapsedTime);
	O.OnPlay(elapsedTime);
	M.OnPlay(elapsedTime);
	num1a.OnPlay(elapsedTime);
	num1b.OnPlay(elapsedTime);
	acute.OnPlay(elapsedTime);
	chicken.OnPlay(elapsedTime);




	return true;
}
