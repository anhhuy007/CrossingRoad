#include "PlayMenuScreen.h"
#include "MenuScreen.h"
#include "ClassicMap.h"
#include "WinterMap.h"

bool PlayMenuScreen::OnCreate() {
	InitWidget();
	return true;
}

bool PlayMenuScreen::OnUpdate(float elapsedTime) {
	// if player press ESC, then back to menu screen
	if (game->inputHandle->keyState_[Keyboard::ESCAPE_KEY].isPressed) {
		CrossingRoad::Navigation::To(new MenuScreen(game));
	}

	game->RenderSprite(bgImage, { 0, 0 });
	playMenuWidget.Update(elapsedTime);

	return true;
}

void PlayMenuScreen::InitWidget()
{
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

	game->SetConsoleColor(colors);

	// declaration

	std::vector<Widget::Button> buttons = {
		Widget::Button(
			game,
			"ENDLESS MODE",
			[&]() {
				OnEndlessModeClicked();
			}
		),
		Widget::Button(
			game,
			"LEVEL MODE",
			[&]() {
				OnLevelModeClicked();
			}
		),
		Widget::Button(
			game,
			"LOAD GAME",
			[&]() {
				CrossingRoad::Navigation::To(new SavedGameScreen(game));
				//OnLoadGameClicked();
			}
		),
		Widget::Button(
			game,
			"BACK",
			[&]() {
				CrossingRoad::Navigation::To(new MenuScreen(game));
			}
		),
	};

	playMenuWidget = MenuWidget(
		game,
		buttons,
		{ 150, 50 }
	);

	bgImage = Image(DrawableRes::WhiteBG, Overlapped::BACKGROUND);
}

void PlayMenuScreen::OnLevelModeClicked()
{
	int random = rand() % 2;
	if (random == 0) {
		CrossingRoad::Navigation::To(new ClassicMap(game, GameMode::LEVEL_MODE));
	}
	else {
		CrossingRoad::Navigation::To(new WinterMap(game, GameMode::LEVEL_MODE));
	}
}

void PlayMenuScreen::OnEndlessModeClicked()
{
	int random = rand() % 2;
	if (random == 0) {
		CrossingRoad::Navigation::To(new ClassicMap(game, GameMode::ENDLESS_MODE));
	}
	else {
		CrossingRoad::Navigation::To(new WinterMap(game, GameMode::ENDLESS_MODE));
	}
}

void PlayMenuScreen::OnLoadGameClicked()
{
	GameMapInfo savedGame;
	std::string savedGameName = GetSavedGameName();
	bool status = FileIO::LoadGameInfo(savedGameName + ".game", savedGame);
 
	if (status == false) {
		std::cout << "Load game failed!" << std::endl;
		return;
	}

	if (savedGame.mapType == MapType::CLASSIC) {
		CrossingRoad::Navigation::To(new ClassicMap(game, savedGame));
	}
	else if (savedGame.mapType == MapType::WINTER) {
		CrossingRoad::Navigation::To(new WinterMap(game, savedGame));
	}
}

std::string PlayMenuScreen::GetSavedGameName()
{
	// display screen to ask player to enter game name
	std::string gameName;
	Image bg = Image(DrawableRes::WhiteBG, Overlapped::BACKGROUND);
	Widget::Text title = Widget::Text(
		game,
		"Enter game name: ",
		{ 140, 70 },
		100, 30,
		TextFont::NORMAL,
		6
	);
	Widget::Text inputText = Widget::Text(
		game,
		"name",
		{ 230, 70 },
		200, 30,
		TextFont::NORMAL
	);
	Widget::Text rule = Widget::Text(
		game,
		"Game name must be less than 20 characters and contain no special characters",
		{ 140, 100 },
		200, 30,
		TextFont::NORMAL,
		15
	);

	Widget::Text note = Widget::Text(
		game,
		"Press ENTER to save game or ESC to exit",
		{ 140, 120 },
		200, 40,
		TextFont::NORMAL,
		15
	);

	Widget::Text inputStatus = Widget::Text(
		game,
		"Invalid game name!",
		{ 140, 150 },
		200, 40,
		TextFont::NORMAL,
		10
	);

	// lambda function to check if game name is valid
	auto isValidGameName = [](std::string gameName) {
		if (gameName.size() == 0 || gameName.size() > 20) return false;
		for (auto c : gameName) {
			if (c == ' ') continue;
			if (c < '0' || c > '9') {
				if (c < 'A' || c > 'Z') {
					if (c < 'a' || c > 'z') {
						return false;
					}
				}
			}
		}
		return true;
	};

	// check exist game name
	auto isExistGameName = [](std::string gameName) {
		std::string path = "SavedGame/" + gameName + ".game";
		std::ifstream file(path);
		return file.good();
	};

	// get game name from player
	bool isValid = false;
	bool okGameName = false;
	while (!okGameName) {
		game->inputHandle = InputHandle::GetKeyBoardState();

		if (game->inputHandle->keyState_[Keyboard::ENTER_KEY].isPressed) {
			if (!isExistGameName(gameName)) {
				isValid = false;
				inputStatus.UpdateText("Game name is not exist!");
			}
			else if (isValidGameName(gameName)) {
				okGameName = true;
				inputStatus.UpdateText("Load game succesfully!");
				inputStatus.SetTextColor(8);
			}
		}
		else if (game->inputHandle->keyState_[Keyboard::ESCAPE_KEY].isPressed) {
			return "";
		}
		else for (int i = 0; i < keyNumber; i++) {
			if (game->inputHandle->keyState_[i].isPressed) {
				isValid = isValidGameName(gameName);
				if (!isValid) inputStatus.UpdateText("Invalid game name!");
				else inputStatus.UpdateText("Valid name!");

				if (i == Keyboard::BACKSPACE_KEY) {
					if (gameName.size() > 0) {
						gameName.pop_back();
					}
				}
				else if ((i >= Keyboard::A_KEY && i <= Keyboard::Z_KEY) ||
					(i >= Keyboard::a_KEY && i <= Keyboard::z_KEY) ||
					(i >= Keyboard::NUM_0_KEY && i <= Keyboard::NUM_9_KEY) ||
					i == Keyboard::SPACE_KEY
					) {
					if (gameName.size() < 20) {
						gameName.push_back(i);
					}
				}
			}
		}

		// update input text
		game->ClearConsole();
		game->RenderSprite(bg, { 0, 0 });
		inputText.UpdateText(gameName);
		inputText.Render();
		title.Render();
		rule.Render();
		note.Render();
		inputStatus.Render();
		game->UpdateConsole();
	}

	return gameName;
}

