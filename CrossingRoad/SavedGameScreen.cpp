#include "SavedGameScreen.h"
#include "CrossingRoad.h"
#include "Sound.h"
#include "ClassicMap.h"
#include "WinterMap.h"

void SavedGameScreen::InitWidget()
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
	game->SetConsoleColor(colors);

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
}

std::vector<SavedGameDisplayInfo> SavedGameScreen::GetSavedGameInfo()
{
	std::string path = "SavedGame\\";
	for (const auto& entry : std::filesystem::directory_iterator(path))
	{
		std::string fileName = entry.path().filename().string();
		
		// read file to get saved game info
		GameMapInfo gameInfo;
		bool status = FileIO::LoadGameInfo(fileName, gameInfo);

		if (!status) continue;

		// get display info
		fileName = fileName.substr(0, fileName.find("."));
		savedGameList.push_back(SavedGameDisplayInfo(
			savedGameList.size() + 1,
			gameInfo.playerInfo.playerName,
			fileName,
			gameInfo.gameMode,
			gameInfo.score
		));
	}

	return savedGameList;
}

bool SavedGameScreen::OnCreate()
{
	InitWidget();
	std::vector<SavedGameDisplayInfo> savedGameList = GetSavedGameInfo();

	// display saved game list to table
	COORD pos = { 75, 95 };
	for (int i = 0; i < savedGameList.size(); i++)
	{
		savedGameTexts.push_back(SavedGameText(
			game,
			savedGameList[i],
			pos,
			200, 5,
			TextFont::NORMAL, 0
		));

		pos.Y += 30;
	}

	return true;
}

bool SavedGameScreen::OnUpdate(float elapsedTime)
{
	// if player press ESC, then back to menu screen
	if (game->inputHandle->keyState_[Keyboard::ESCAPE_KEY].isPressed) {
		CrossingRoad::Navigation::To(new MenuScreen(game));
	}

	short top_border = 60, left = 70, space = 28;
	game->RenderSprite(bg, { 0, 0 });
	game->RenderSprite(book, { 20,7 });
	game->RenderSprite(cat, { 390,202 });

	game->RenderSprite(headerItem, { left,top_border }); top_border += 35;
	game->RenderSprite(listItem, { left,top_border }); top_border += 30;
	game->RenderSprite(listItem, { left,top_border }); top_border += 30;
	game->RenderSprite(listItem, { left,top_border }); top_border += 30;
	game->RenderSprite(listItem, { left,top_border }); top_border += 30;

	// render text
	COORD pos = { 75, 105 };
	for (int i = itemRange; i < min(itemRange + 4, savedGameTexts.size()); i++)
	{
		// update text position
		savedGameTexts[i].SetYPosition(pos.Y);
		savedGameTexts[i].Render();

		pos.Y += 30;
	}

	// render header
	for (int i = 0; i < 5; i++) {
		header[i].Render();
	}

	S.OnPlay(elapsedTime);
	A1.OnPlay(elapsedTime);
	V.OnPlay(elapsedTime);
	E1.OnPlay(elapsedTime);
	D.OnPlay(elapsedTime);

	G.OnPlay(elapsedTime);
	A2.OnPlay(elapsedTime);
	M.OnPlay(elapsedTime);
	E2.OnPlay(elapsedTime);

	// update hover
	if (game->inputHandle->keyState_[Keyboard::UP_KEY].isPressed) {
		hoverIndex--;

		if (hoverIndex < 0) {
			hoverIndex = 0;
			game->sound->playEffectSound(int(Sound::Effect::INVALID));
		}
		else {
			game->sound->playEffectSound(int(Sound::Effect::VALID));
			hoverPos.Y -= 30;
		}

		if (hoverIndex < itemRange) {
			itemRange = max(0, itemRange - 1);
			hoverPos.Y += 30;
		}
	}
	else if (game->inputHandle->keyState_[Keyboard::DOWN_KEY].isPressed) {
		hoverIndex++;

		if (hoverIndex >= savedGameTexts.size()) {
			hoverIndex = savedGameTexts.size() - 1;
			game->sound->playEffectSound(int(Sound::Effect::INVALID));
		}
		else {
			game->sound->playEffectSound(int(Sound::Effect::VALID));
			hoverPos.Y += 30;
		}

		if (hoverIndex >= itemRange + 4) {
			itemRange = min(itemRange + 1, savedGameTexts.size() - 4);
			hoverPos.Y -= 30;
		}
	}

	hover.SetPosition(hoverPos);
	hover.OnPlay(elapsedTime);

	// handle enter key pressed
	if (game->inputHandle->keyState_[Keyboard::ENTER_KEY].isPressed) {
		if (savedGameList.size() == 0) return true;

		game->sound->playEffectSound(int(Sound::Effect::ENTER));
		// get saved game info
		SavedGameDisplayInfo info = savedGameList[hoverIndex];

		// load saved game
		GameMapInfo gameInfo;
		bool status = FileIO::LoadGameInfo(info.fileName + ".game", gameInfo);
		
		if (!status) return false;

		// navigate to game screen
		if (gameInfo.mapType == MapType::CLASSIC) {
			CrossingRoad::Navigation::To(new ClassicMap(game, gameInfo));
		}
		else if (gameInfo.mapType == MapType::WINTER) {
			CrossingRoad::Navigation::To(new WinterMap(game, gameInfo));
		}
	}

	return true;
}

SavedGameScreen::SavedGameText::SavedGameText(
	CrossingRoad* _game,
	SavedGameDisplayInfo _info,
	COORD _position,
	int _width,
	int _height,
	TextFont _font,
	short _color
) {
	game = _game;
	info = _info;
	position = _position;

	number = Widget::Text(
		game,
		std::to_string(info.index),
		{ short(position.X + 10), short(position.Y + 10) },
		_width, _height,
		_font, _color
	);

	playerName = Widget::Text(
		game,
		info.playerName,
		{ short(position.X + 35), short(position.Y + 10) },
		_width, _height,
		_font, _color
	);

	gameName = Widget::Text(
		game,
		info.fileName,
		{ short(position.X + 120), short(position.Y + 10) },
		_width, _height,
		_font, _color
	);

	gameMode = Widget::Text(
		game,
		(info.gameMode == GameMode::ENDLESS_MODE) ? "ENDLESS" : "LEVEL",
		{ short(position.X + 220), short(position.Y + 10) },
		_width, _height,
		_font, _color
	);

	score = Widget::Text(
		game,
		std::to_string(info.score),
		{ short(position.X + 280), short(position.Y + 10) },
		_width, _height,
		_font, _color
	);
}

void SavedGameScreen::SavedGameText::Render()
{
	number.Render();
	playerName.Render();
	gameName.Render();
	gameMode.Render();
	score.Render();
}

void SavedGameScreen::SavedGameText::SetYPosition(int _position)
{
	position.Y = _position;
	// update text position
	number.UpdatePosition({number.getPosition().X, position.Y});
	playerName.UpdatePosition({ playerName.getPosition().X, position.Y });
	gameName.UpdatePosition({ gameName.getPosition().X, position.Y });
	gameMode.UpdatePosition({ gameMode.getPosition().X, position.Y });
	score.UpdatePosition({ score.getPosition().X, position.Y });
}
