#include "SavedGameScreen.h"

bool SavedGameScreen::OnCreate()
{
	//S A V E D G M
	std::vector<Graphic::Sprite> textSgif = {
		Graphic::Sprite(DrawableRes::saveGameTitleCharSwithShadow),
		Graphic::Sprite(DrawableRes::saveGameTitleCharSwithoutShadow),
	};
	std::vector<Graphic::Sprite> textAgif = {
	Graphic::Sprite(DrawableRes::saveGameTitleCharAwithShadow),
	Graphic::Sprite(DrawableRes::saveGameTitleCharAwithoutShadow),
	};
	std::vector<Graphic::Sprite> textVgif = {
	Graphic::Sprite(DrawableRes::saveGameTitleCharVwithShadow),
	Graphic::Sprite(DrawableRes::saveGameTitleCharVwithoutShadow),
	};
	std::vector<Graphic::Sprite> textEgif = {
		Graphic::Sprite(DrawableRes::saveGameTitleCharEwithShadow),
		Graphic::Sprite(DrawableRes::saveGameTitleCharEwithoutShadow),
	};
	std::vector<Graphic::Sprite> textDgif = {
		Graphic::Sprite(DrawableRes::saveGameTitleCharDwithShadow),
		Graphic::Sprite(DrawableRes::saveGameTitleCharDwithoutShadow),
	};
	std::vector<Graphic::Sprite> textGgif = {
		Graphic::Sprite(DrawableRes::saveGameTitleCharGwithShadow),
		Graphic::Sprite(DrawableRes::saveGameTitleCharGwithoutShadow),
	};
	std::vector<Graphic::Sprite> textMgif = {
		Graphic::Sprite(DrawableRes::saveGameTitleCharMwithShadow),
		Graphic::Sprite(DrawableRes::saveGameTitleCharMwithoutShadow),
	};
	
	std::string animationPath = "Screen\\saveGame\\animation\\hoverGif\\";
	std::vector<Graphic::Sprite> hoverGif;
	for (int i = 1; i <= 6; i++)
	{
		hoverGif.push_back(Graphic::Sprite(animationPath + "frame" + std::to_string(i) + ".sprite"));
	}

	//-----------------------------COLOR SAVEGAME---------------------------
	std::vector<int> colors = {
	RGB(0, 0, 0),  // BLACK
	RGB(255, 255, 255),  // WHITE
	RGB(227, 134, 132),  // PINK
	RGB(168, 208, 230),  // LIGHT BLUE + bg
	RGB(15, 47, 67),  // DARK BLUE
	RGB(255, 235, 216),  // YELLOW HEADER
	RGB(43, 122, 120),  // BORDER GREEN

	RGB(226,63,166), //DARK RED
	//book
	RGB(237,28,36), //RED
	RGB(143,25,194), //PURPLE
	RGB(255,242,0), //YELLOW
	RGB(171,181,193), //DARK GRAY
	RGB(232,233,235), //LIGHT GRAY
	//cat
	RGB(187,213,245), //LIGHT BLUE
	RGB(118,151,201), //BLUE
	RGB(246,165,151), //LIGHT PINK

	//16 / 16

	};
	COLOR::SetConsoleColor(colors);

	short top_border = 10, left = 100, space = 28;
	S = Animation(game, textSgif, { left, top_border }, 400); left += space;
	A1 = Animation(game, textAgif, { left, top_border }, 400); left += space;
	V = Animation(game, textVgif, { left, top_border }, 400); left += space;
	E1 = Animation(game, textEgif, { left, top_border }, 400); left += space;
	D = Animation(game, textDgif, { left, top_border }, 400); left += (space + 15);

	G = Animation(game, textGgif, { left, top_border }, 400); left += space;
	A2 = Animation(game, textAgif, { left, top_border }, 400); left += space;
	M = Animation(game, textMgif, { left, top_border }, 400); left += space;
	E2 = Animation(game, textEgif, { left, top_border }, 400); left += space;

	hover = Animation(game, hoverGif, { 70, 125 }, 100);

	//-----------------------------DECLARATION---------------------------

	bg = Image("Screen\\saveGame\\img\\bgSaveGame.sprite");
	headerItem = Image("Screen\\saveGame\\img\\headerItem.sprite");
	listItem = Image("Screen\\saveGame\\img\\listItem.sprite");
	book = Image("Screen\\saveGame\\img\\book.sprite");
	cat = Image("Screen\\saveGame\\img\\cat.sprite");

	return true;
}

bool SavedGameScreen::OnUpdate(float elapsedTime)
{
	short top_border = 60, left = 70, space = 28;
	game->RenderSprite(bg, { 0, 0 });
	game->RenderSprite(book, { 20,7 });
	game->RenderSprite(cat, { 390,202 });

	game->RenderSprite(headerItem, { left,top_border }); top_border += 35;
	game->RenderSprite(listItem, { left,top_border }); top_border += 30;
	game->RenderSprite(listItem, { left,top_border }); top_border += 30;
	game->RenderSprite(listItem, { left,top_border }); top_border += 30;
	game->RenderSprite(listItem, { left,top_border }); top_border += 30;

	S.OnPlay(elapsedTime);
	A1.OnPlay(elapsedTime);
	V.OnPlay(elapsedTime);
	E1.OnPlay(elapsedTime);
	D.OnPlay(elapsedTime);

	G.OnPlay(elapsedTime);
	A2.OnPlay(elapsedTime);
	M.OnPlay(elapsedTime);
	E2.OnPlay(elapsedTime);

	hover.OnPlay(elapsedTime);

	return true;
}
