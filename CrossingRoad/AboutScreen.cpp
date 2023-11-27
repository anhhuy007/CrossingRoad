#include "AboutScreen.h"
#include "MenuScreen.h"
#include "StreetMap.h"

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
		{ 150,100 }
	);

	image = Image(DrawableRes::LightBlueBG, Overlapped::BACKGROUND);
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
