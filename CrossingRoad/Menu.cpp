#include "Menu.h"

bool Menu::OnCreate() {
	std::vector<Graphic::Sprite> gifs = {
		Graphic::Sprite("animations\\meow\\frame1.sprite"),
		Graphic::Sprite("animations\\meow\\frame2.sprite"),
		Graphic::Sprite("animations\\meow\\frame3.sprite"),
		Graphic::Sprite("animations\\meow\\frame4.sprite"),
		/*Graphic::Sprite("animations\\chickensplashscreen\\frame5.sprite"),
		Graphic::Sprite("animations\\chickensplashscreen\\frame6.sprite"),
		Graphic::Sprite("animations\\chickensplashscreen\\frame7.sprite"),
		Graphic::Sprite("animations\\chickensplashscreen\\frame8.sprite"),
		Graphic::Sprite("animations\\chickensplashscreen\\frame9.sprite"),*/
	};

	

	// set console color
	vector<int> colors = {
			RGB(0, 0, 0),
			RGB(255, 255, 255),
			RGB(174, 222, 102),
			RGB(159, 204, 92),
			RGB(110, 184, 46),
			RGB(12, 67, 57),
			RGB(127, 137, 173),
			RGB(96, 109, 138),
			RGB(72, 78, 94),
			RGB(113, 215, 255),
			RGB(126, 74, 76),
			RGB(10,50,103),
			RGB(252,137,174), 
			RGB(253,218,133), 
			RGB(101,166,255), 
			RGB(153,152,154)
	};
	COLOR::SetConsoleColor(colors);

	// declaration
	Widget::Text text(game, "CROSSING ROAD", { 50, 10 }, TextFont::NORMAL);
	meow = Animation(game, gifs, { 100, 10 }, 100);
	chick = new GamePlayer(Player::CHICK, game);

	return true;
}

bool Menu::OnUpdate(float elapsedTime) {
	chick->Update(elapsedTime);
	
	chick->Render();
	meow.OnPlay(elapsedTime);

	return true;
}