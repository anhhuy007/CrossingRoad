#include "LeaderBoard.h" 

bool LeaderBoard::OnCreate()
{
	//-----------------------------LEADER BOARD---------------------------
	std::vector<int> colors = {
		RGB(0,0,0), //BLACK
		RGB(255,255,255), // WHITE 
		RGB(253,143,144), //LIGHT RED
		RGB(236,74,75), //RED
		RGB(253,195,59),	//MEDAL 1 LIGHT YELLOW
		RGB(223,162,37), 	//MEDAL 1 STRONG YELLOW
		RGB(183,181,206), 	//MEDAL 2 LIGHT GRAY
		RGB(116,139,166), 	//MEDAL 2 STRONG GRAY
		RGB(226,146,103), 	//MEDAL 3 LIGHT BRONZE
		RGB(194,104,77) ,	//MEDAL 3 STRONG BRONZE

		RGB(0,186,255), // bg
		RGB(43,122,120), // border item
		RGB(255,235,216), //content padding
		RGB(159,250,222), // title
		//14/16
	};	

	bg = Image(DrawableRes::leaderboardBg);
	item = Image(DrawableRes::leaderboardItem);
	title = Image(DrawableRes::title);
	text1 = Image(DrawableRes::endlessText);
	text2 = Image(DrawableRes::levelText);
	medal1 = Image(DrawableRes::goldMedal);
	medal2 = Image(DrawableRes::silverMedal);
	medal3 = Image(DrawableRes::bronzeMedal);

	COLOR::SetConsoleColor(colors);

    return true;
}

bool LeaderBoard::OnUpdate(float elapsedTime)
{
	// if player press ESC, then back to menu screen
	if (game->inputHandle->keyState_[Keyboard::ESCAPE_KEY].isPressed) {
		CrossingRoad::Navigation::To(new MenuScreen(game));
	}

	short left = 45, top = 90;
	game->RenderSprite(bg, { 0,0 });
	game->RenderSprite(title, { 86,20});
	game->RenderSprite(text1, { 73,short(top - 30) });
	game->RenderSprite(text2, { 310,short(top - 30) });

	game->RenderSprite(medal1, { 15,short(top - 5) });
	game->RenderSprite(medal2, { 15,short(top +35 ) });
	game->RenderSprite(medal3, { 15,short(top +75) });

	game->RenderSprite(medal1, { 240,short(top - 5) });
	game->RenderSprite(medal2, { 240,short(top + 35) });
	game->RenderSprite(medal3, { 240,short(top + 75) });


	for (int i = 0; i < 3; i++)
	{
		game->RenderSprite(item, { left,top });
		game->RenderSprite(item, { short(left+225),top });
		top += 40;
	}
	return true;
}
