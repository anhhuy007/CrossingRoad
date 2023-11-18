#include "Menu.h"
#include "StreetMap.h"

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

	COLOR::SetConsoleColor(colors);

	// declaration
	
	text = Widget::Text(
		game, 
		"It was developed and published by Australian video game developer Hipster Whale", 
		{ 10, 10 }, 
		100, 
		100,
		TextFont::NORMAL
	);

	button = Widget::Button(
		game,
		"Play",
		[]() { cout << "NewGame" << endl; },
		{ 100, 100 }
	);

	std::vector<Widget::Button> buttons = {
		Widget::Button(
			game,
			"Play",
			[&]() {
				CrossingRoad::Navigation::To(new StreetMap(game));
			}
		),
		Widget::Button(
			game,
			"Setting",
			[]() { }
		),
		Widget::Button(
			game,
			"About",
			[]() { }
		),
	};

	menuWidget = MenuWidget(
		game,
		buttons,
		{ 100, 50 }
	);

	image = Image(DrawableRes::WhiteBG, Overlapped::LAND);
	meow = Animation(game, gifs, { 100, 10 }, 100);
	chick = new GamePlayer(Player::CHICK, game);

	return true;
}

bool Menu::OnUpdate(float elapsedTime) {
	chick->Update(elapsedTime);
	
	/*text.Render();
	button.Render();*/
	game->RenderSprite(image, { 0, 0 });
	//meow.OnPlay(elapsedTime);

	menuWidget.Update(elapsedTime);

	return true;
}