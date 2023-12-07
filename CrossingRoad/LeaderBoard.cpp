#include "LeaderBoard.h" 

void LeaderBoard::InitWidget()
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
	esc = Image(DrawableRes::escText);

	game->SetConsoleColor(colors);
}

bool LeaderBoard::OnCreate()
{
	InitWidget();
	GetLeaderBoardInfo();

	// sort saved game list by score
	std::sort(leaderBoardInfos.begin(), leaderBoardInfos.end(), [](LeaderBoardInfo a, LeaderBoardInfo b) {
		return a.score > b.score;
	});

	// display saved game list to table
	COORD pos = { 45, 90 };
	for (int i = 0; i < leaderBoardInfos.size(); i++)
	{
		if (leaderBoardInfos[i].gameMode == GameMode::ENDLESS_MODE) {
			endlessLBTexts.push_back(LeaderBoardText(
				game,
				pos,
				leaderBoardInfos[i],
				110, 5,
				TextFont::NORMAL, 0
			));

			pos.Y += 42;
		}
	}

	// sort saved game list by level
	std::sort(leaderBoardInfos.begin(), leaderBoardInfos.end(), [](LeaderBoardInfo a, LeaderBoardInfo b) {
		return a.level > b.level;
	});

	pos = { 270, 90 };
	for (int i = 0; i < leaderBoardInfos.size(); i++) {
		if (leaderBoardInfos[i].gameMode == GameMode::LEVEL_MODE) {
			levelLBTexts.push_back(LeaderBoardText(
				game,
				pos,
				leaderBoardInfos[i],
				110, 5,
				TextFont::NORMAL, 0
			));

			pos.Y += 42;
		}
	}

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

	game->RenderSprite(esc, { 132, 211 });

	for (int i = 0; i < 3; i++)
	{
		game->RenderSprite(item, { left,top });
		game->RenderSprite(item, { short(left+225),top });
		top += 40;
	}

	// render player name and score
	int boardSize = levelLBTexts.size() > 3 ? 3 : levelLBTexts.size();
	for (int i = 0; i < boardSize; i++) {
		levelLBTexts[i].Render();
	}

	boardSize = endlessLBTexts.size() > 3 ? 3 : endlessLBTexts.size();
	for (int i = 0; i < boardSize; i++) {
		endlessLBTexts[i].Render();
	}

	return true;
}

void LeaderBoard::GetLeaderBoardInfo()
{
	// get all saved game info
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
		leaderBoardInfos.push_back(LeaderBoardInfo(
			gameInfo.playerInfo.playerName,
			gameInfo.score,
			gameInfo.level,
			gameInfo.gameMode
		));
	}
}

LeaderBoard::LeaderBoardText::LeaderBoardText(
	CrossingRoad* pgame, 
	COORD pposition, 
	LeaderBoardInfo pinfo, 
	int pwidth, int pheight,
	TextFont pfont, 
	short pcolor
) {
	game = pgame;
	position = pposition;
	info = pinfo;

	playerName = Widget::Text(
		game,
		info.playername,
		Widget::GetCenterTextPos(
			info.playername,
			position,
			104, 22
		),
		104, 22,
		TextFont::NORMAL,
		0
	);

	int _score = info.gameMode == GameMode::ENDLESS_MODE ? info.score : info.level;
	score = Widget::Text(
		game, 
		std::to_string(_score),
		Widget::GetCenterTextPos(
			std::to_string(info.score),
			{ short(position.X + 104), position.Y },
			54, 22
		),
		54, 22,
		TextFont::NORMAL, 
		0
	);
}

void LeaderBoard::LeaderBoardText::Render()
{
	playerName.Render();
	score.Render();
}

void LeaderBoard::LeaderBoardText::SetYPosition(int yPos)
{
	position.Y = yPos;
	playerName.UpdatePosition(position);
	score.UpdatePosition(position);
}
