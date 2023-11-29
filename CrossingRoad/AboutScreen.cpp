#include "AboutScreen.h"
#include "MenuScreen.h"


bool AboutScreen::OnCreate() {
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

	std::vector<Widget::Button> buttons = {
		Widget::Button(
			game,
			"BACK",
			[&]() {
				CrossingRoad::Navigation::To(new MenuScreen(game));
			}
		)
	};

	aboutMenuWidget = MenuWidget(
		game,
		buttons,
		{ 155, 180 }
	);

	image = Image(DrawableRes::LightBlueBG, Overlapped::BACKGROUND);
	design = Widget::Text(game, "DESIGNED BY TEAM 11 HCMUS", { 175,60 }, 140, 5, TextFont::NORMAL);
	mssv1 = Widget::Text(game, "22127086 Nguyen Lam Anh Duy", { 170,75 }, 150, 5, TextFont::NORMAL);
	mssv2 = Widget::Text(game, "22127149 Huynh Anh Huy", { 183,90 }, 120, 5, TextFont::NORMAL);
	mssv3 = Widget::Text(game, "22127348 Phan Nguyen Hoang Quan", { 160,105 }, 170, 5, TextFont::NORMAL);
	mssv4 = Widget::Text(game, "22127141 Ngo Hoang Nam Hung", { 175,120 }, 170, 5, TextFont::NORMAL);
	instructor = Widget::Text(game, "Instructor Truong Toan Thinh", { 170,135 }, 150, 5, TextFont::NORMAL);
	releasedDate = Widget::Text(game, "Released Date 15 December", { 180,150 }, 170, 5, TextFont::NORMAL);
	Version = Widget::Text(game, "This is the first version", { 170,165 }, 180, 5, TextFont::NORMAL);
	return true;	
}

bool AboutScreen::OnUpdate(float elapsedTime) {
	// draw background
	game->RenderSprite(image, { 0, 0 });
	//Print text

	design.Render();
	mssv1.Render();
	mssv2.Render();
	mssv3.Render();
	mssv4.Render();
	instructor.Render();
	releasedDate.Render();
	Version.Render();

	// update menu
	aboutMenuWidget.Update(elapsedTime);
    return true;
}
