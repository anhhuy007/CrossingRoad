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
	COLOR::SetConsoleColor(colors);
	

	bg = Image(DrawableRes::leaderboardBg);
	item = Image(DrawableRes::leaderboardItem);
	title = Image(DrawableRes::title);
	text1 = Image(DrawableRes::endlessText);
	text2 = Image(DrawableRes::levelText);
	medal1 = Image(DrawableRes::goldMedal);
	medal2 = Image(DrawableRes::silverMedal);
	medal3 = Image(DrawableRes::bronzeMedal);



    return true;
}

bool LeaderBoard::OnUpdate(float elapsedTime)
{
	game->RenderSprite(bg, { 0,0 });
	game->RenderSprite(title, { 86,10 });
	game->RenderSprite(text1, { 73,48 });
	game->RenderSprite(text2, { 310,48 });

	game->RenderSprite(medal1, { 10,60 });
	game->RenderSprite(medal2, { 10,92 });
	game->RenderSprite(medal3, { 10,124 });

	game->RenderSprite(medal1, { 235,60 });
	game->RenderSprite(medal2, { 235,92 });
	game->RenderSprite(medal3, { 235,124 });

	short left = 40, top = 67;
	for (int i = 0; i < 5; i++)
	{
		game->RenderSprite(item, { left,top });
		game->RenderSprite(item, { short(left+225),top });
		top += 32;
	}
	return true;
}
