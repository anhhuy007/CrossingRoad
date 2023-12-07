#include "GameMap.h"
#include "WaterLane.h"
#include "RoadLane.h"
#include "WinterMap.h"
#include "ClassicMap.h"

const std::vector<std::pair<MapType, int>> gameLevels = {
	{ MapType::WINTER, 20 },
	{ MapType::WINTER, 20 },
	{ MapType::CLASSIC, 20 },
	{ MapType::CLASSIC, 30 },
	{ MapType::WINTER, 30 },
	{ MapType::WINTER, 30 },
	{ MapType::CLASSIC, 30 },
	{ MapType::WINTER, 40 },
	{ MapType::CLASSIC, 40 },
};

void GameMap::CreateNewGame()
{
	player = new GamePlayer(game->userOption.player, game);
	portal = Portal(game);
	grid = Graphic::Sprite(DrawableRes::Grid, Overlapped::PLAYER);
	maxIndex = 14;

	if (gameInfo.gameMode == GameMode::ENDLESS_MODE) {
		// create random game lanes
		gameInfo.endLane = 300;
		gameInfo.level = 0;
	}

	CreateLanes();
}

void GameMap::LoadSavedGame()
{
	// initialize player
	player = new GamePlayer(gameInfo.playerInfo, game);

	if (gameInfo.gameMode == GameMode::LEVEL_MODE) {
		// build portal for level mode
		portal = Portal(game);
		portal.setPosition(gameInfo.portalInfo.position);
		portal.visible = gameInfo.portalInfo.visible;
		portal.lanePos = gameInfo.portalInfo.lanePos;
	}

	LoadSavedLanes();
}

bool GameMap::OnCreate()
{
	if (gameInfo.lanesInfo.size() == 0) {
		CreateNewGame();
	}
	else {
		LoadSavedGame();
	}

	// play sound
	if (gameInfo.mapType == MapType::CLASSIC) {
		game->sound->playBackgroundSound(int(Sound::Background::HIGHWAY));
	}
	else {
		game->sound->playBackgroundSound(int(Sound::Background::CHRISTMAS));
	}

	InitWidget();

	return true;
}

bool GameMap::OnUpdate(float elapsedTime) {
	if (player->animationState == AnimationState::DEAD || player->animationState == AnimationState::DROWN) {
		totalTime += elapsedTime;
		if (totalTime > 2000) {
			totalTime = 2000;
			// display dialog to ask player to continue or exit game
			gameover_dialog.Update(30);
			gameover_dialog.Render();
		}
	}

	if (!isPaused) {
		// update lanes and player position
		for (int i = 0; i < lanes.size(); i++) {
			lanes[i]->Update(elapsedTime);
		}

		// disable player moving above lane containing portal
		if (portal.lanePos != 9 || player->lanePos != 7 || !game->inputHandle->keyState_[Keyboard::UP_KEY].isPressed) {
			player->Update(elapsedTime);
		}

		// check for game collision
		if (portal.lanePos == 9) portal.WriteCollisionPoints();
		if (HandlePlayerCollision(elapsedTime) == false) {
			// if player win
			return true;
		};

		// update score
		int playerPos = player->lanePos;
		if (playerPos < maxIndex) {
			maxIndex = playerPos;
			gameInfo.score++;
		}
	}

	// display game 
	Render();

	if (isPaused) {
		return OnPause();
	}

	// handle map scrolling up
	int playerPos = player->lanePos;
	if (playerPos == 6 && portal.lanePos != 9) {
		ScrollUp();
		player->MoveDown(player->lanePos);
		if (portal.visible) portal.MoveDown(portal.lanePos);
		maxIndex++;
	}

	return true;
}

bool GameMap::OnPause() {
	if (player->animationState == AnimationState::DEAD || player->animationState == AnimationState::DROWN) {
		return true;
	}

	// display dialog to ask player to continue or exit game
	isPaused = true;
	pausegame_dialog.Update(30);
	pausegame_dialog.Render();

	return true;
}


void GameMap::Render() {
	for (int i = 0; i < lanes.size(); i++) {
		if (portal.lanePos == i) portal.Render();
		lanes[i]->Render();
		if (player->lanePos == i) player->Render();
	}

	// update text 
	std::string str_score = std::to_string(gameInfo.score);
	std::string str_coin = std::to_string(gameInfo.coin);

	Widget::Text textScore = Widget::Text(
		game,
		str_score,
		{ short(440 - str_score.length() * 13 + 13), 5 },
		50, 30,
		TextFont::NUMBER
	);

	// display collected coins
	Widget::Text textCoins = Widget::Text(
		game,
		str_coin,
		{ short(440 - str_coin.length() * 13 + 13), 22 },
		50, 30,
		TextFont::COIN_NUMBER
	);

	if (gameInfo.gameMode == GameMode::LEVEL_MODE) {
		Image textLevel = Image(DrawableRes::LevelText, Overlapped::TEXT);
		game->RenderSprite(textLevel, { 10, 5 });
		level.Render();
	}

	// display score
	textScore.Render();
	textCoins.Render();
}

bool GameMap::HandlePlayerCollision(float elapsedTime) {
	int collisType = player->CheckCollision();

	COORD pos = player->getPosition();

	if (collisType != 5 || game->inputHandle->keyState_[Keyboard::UP_KEY].isPressed || game->inputHandle->keyState_[Keyboard::DOWN_KEY].isPressed) {
		isFirstOnLog = false;
	}
	if (collisType == 5) {
		if (player->animationState == AnimationState::DROWN) {
			if (!isFirstHit) {
				game->sound->playEffectSound(int(Sound::Effect::WATER_SPLASH));
				game->sound->playEffectSound(int(Sound::Effect::END_WINTER_MAP));
				isFirstHit = true;
				return true;
			}
		}
		if (!isFirstOnLog) {
			if (player->animationState != AnimationState::DROWN) {
				game->sound->playEffectSound(int(Sound::Effect::LOG));
				isFirstOnLog = true;
			}
		}
		// player is on floating object
		Log log = GetLogByLaneId(player->lanePos + 1);
		float logSpeed = log.logSpeed;
		MovingDirection logDirection = log.movingDirection;

		player->MoveHorizontal(
			elapsedTime,
			logSpeed,
			logDirection
		);
	}
	else if (collisType == 4) {
		// player is on water
		if (lanes[player->lanePos + 1]->laneType == LaneType::WATER) {
			player->animationState = AnimationState::DROWN;
			if (!isFirstHit) {
				game->sound->playEffectSound(int(Sound::Effect::WATER_SPLASH));
				game->sound->playEffectSound(int(Sound::Effect::END_WINTER_MAP));
				isFirstHit = true;
			}
		}
		// player is hit by car
		else {
			player->animationState = AnimationState::DEAD;
			if (!isFirstHit) {
				game->sound->playEffectSound(int(Sound::Effect::HIT));
				game->sound->playEffectSound(int(Sound::Effect::END_WINTER_MAP));
				isFirstHit = true;
			}
		}
	}
	else if (collisType == 6) {
		// player hit the portal
		game->sound->playEffectSound(int(Sound::Effect::PORTAL));

		GameMapInfo newGameInfo;
		newGameInfo.gameMode = gameInfo.gameMode;
		newGameInfo.coin = gameInfo.coin + 5;
		newGameInfo.level = gameInfo.level + 1;
		newGameInfo.mapType = gameLevels[newGameInfo.level].first;
		newGameInfo.endLane = gameLevels[newGameInfo.level].second;

		if (gameInfo.mapType == MapType::WINTER) {
			CrossingRoad::Navigation::To(new WinterMap(game, newGameInfo));
		}
		else {
			CrossingRoad::Navigation::To(new ClassicMap(game, newGameInfo));
		}
	}
	else if (collisType == 2) {
		// player hit the coin
		game->sound->playEffectSound(int(Sound::Effect::COIN));
		gameInfo.coin++;
		RoadLane* lane = dynamic_cast<RoadLane*>(lanes[player->lanePos + 1]);
		lane->coin.isCollected = true;
	}

	return true;
}

void GameMap::InitWidget()
{
	// widgets
	std::vector<Widget::Button> buttons = {
		Widget::Button(
			game,
			"Exit",
			[&]() {
				game->sound->pauseEffectSound();
				CrossingRoad::Navigation::To(new MenuScreen(game));
			}
		),
		Widget::Button(
			game,
			"Save game",
			[&]() {
				SaveGame();
			}
		),
		Widget::Button(
			game,
			"Continue",
			[&]() {
				isPaused = false;
			}
		),
	};

	std::string message = "Choose your option";
	pausegame_dialog = Widget::Dialog(
		game,
		message,
		buttons,
		{ 100, 50 }
	);
	std::vector<Widget::Button> buttons2 = {
		Widget::Button(
			game,
			"Exit",
			[&]() {
				CrossingRoad::Navigation::To(new MenuScreen(game));
			}
		),
		Widget::Button(
			game,
			"New game",
			[&]() {
				// reset game info
				GameMapInfo newGameInfo;
				newGameInfo.gameMode = gameInfo.gameMode;
				newGameInfo.coin = 0;
				newGameInfo.level = 1;
				newGameInfo.mapType = gameLevels[newGameInfo.level - 1].first;
				newGameInfo.endLane = gameLevels[newGameInfo.level - 1].second;

				if ((rand() % 2) == 0) {
					CrossingRoad::Navigation::To(new ClassicMap(game, newGameInfo));
				}
				else {
					CrossingRoad::Navigation::To(new WinterMap(game, newGameInfo));
				}
			}
		),
	};

	Image gameoverImg = Image(DrawableRes::GameOver, Overlapped::DIALOG);
	gameover_dialog = Widget::Dialog(
		game,
		Image(DrawableRes::GameOverDialog, Overlapped::DIALOG),
		gameoverImg,
		buttons2,
		{ 100, 50 }
	);

	level = Widget::Text(
		game,
		std::to_string(gameInfo.level),
		{ 10, 20 },
		30, 30,
		TextFont::NUMBER
	);

	SetScreenColor();
}

void GameMap::GetNewEndlessGame()
{
	// generate new endless game
	gameInfo.gameMode = GameMode::ENDLESS_MODE;
	gameInfo.endLane = -1;

	CreateLanes();
}

void GameMap::GetNewGameLevel(int level)
{
	// get new game level info
	gameInfo.mapType = gameLevels[level - 1].first;
	gameInfo.endLane = gameLevels[level - 1].second;

	CreateLanes();
}

void GameMap::SaveGame()
{
	std::pair<std::string, std::string> gameNameInfo = GetSavedNameInfo();
	player->name = gameNameInfo.first;

	GameMapInfo finalInfo = GetGameMapInfo(gameInfo, player, lanes);
	bool status = FileIO::WriteGameInfo(gameNameInfo.second + ".game", finalInfo);

	if (status == true) {
		std::cout << "Game saved successfully" << std::endl;
	}
	else {
		std::cout << "Game saved failed" << std::endl;
	};

	// sleep for 1 seconds
	std::this_thread::sleep_for(std::chrono::milliseconds(1000));
}

std::pair<std::string, std::string> GameMap::GetSavedNameInfo()
{
	// display screen to ask player to enter game name
	std::string gameName, playerName;
	int inputIndex = 0;
	Image bg = Image(DrawableRes::WhiteBG, Overlapped::BACKGROUND);
	Image cursor = Image(DrawableRes::cursor, Overlapped::TEXT);
	Widget::Text title1 = Widget::Text(
		game,
		"Enter player name: ",
		{ 140, 70 },
		100, 30,
		TextFont::NORMAL,
		6
	);
	Widget::Text title2 = Widget::Text(
		game,
		"Enter game name: ",
		{ 140, 80 },
		100, 30,
		TextFont::NORMAL,
		6
	);
	Widget::Text inputText1 = Widget::Text(
		game,
		"name",
		{ 240, 70 },
		200, 30,
		TextFont::NORMAL
	);
	Widget::Text inputText2 = Widget::Text(
		game,
		"name",
		{ 240, 80 },
		200, 30,
		TextFont::NORMAL
	);
	Widget::Text rule = Widget::Text(
		game,
		"Name must be less than 20 characters and contain no special characters",
		{ 140, 110 },
		200, 30,
		TextFont::NORMAL,
		15
	);

	Widget::Text note = Widget::Text(
		game,
		"Press ENTER to save game or ESC to exit",
		{ 140, 130 },
		200, 40,
		TextFont::NORMAL,
		15
	);

	Widget::Text inputStatus = Widget::Text(
		game,
		"Invalid name!",
		{ 140, 160 },
		200, 40,
		TextFont::NORMAL,
		10
	);

	// lambda function to check if game name is valid
	auto isValidName = [](std::string& name) {
		if (name.size() == 0 || name.size() > 11) return false;
		for (auto c : name) {
			if (c == ' ') continue;
			if (c < '0' || c > '9') {
				if (c < 'A' || c > 'Z') {
					if (c < 'a' || c > 'z') {
						return false;
					}
				}
			}
		}
		
		// trim space
		while (name[0] == ' ') {
			name.erase(0, 1);
		}

		while (name[name.size() - 1] == ' ') {
			name.erase(name.size() - 1, 1);
		}

		return name.length() > 0;
		};

	// check exist game name
	auto isExistGameName = [](std::string name) {
		std::string path = "SavedGame/" + name + ".game";
		std::ifstream file(path);
		return file.good();
	};

	// get game name from player
	bool validGameName = false;
	bool validPlayerName = false;
	bool okGameName = false;

	while (!okGameName) {
		game->inputHandle = InputHandle::GetKeyBoardState();
		if (game->inputHandle->keyState_[Keyboard::UP_KEY].isPressed) {
			inputIndex = max(0, inputIndex - 1);
		}
		else if (game->inputHandle->keyState_[Keyboard::DOWN_KEY].isPressed) {
			inputIndex = min(1, inputIndex + 1);
		}
		else if (game->inputHandle->keyState_[Keyboard::ENTER_KEY].isPressed) {
			if (isExistGameName(gameName)) {
				validGameName = false;
				inputStatus.UpdateText("Game name is exist!");
			}
			else if (!isValidName(gameName)) {
				inputStatus.UpdateText("Invalid game name");
			}
			else if (!isValidName(playerName)) {
				inputStatus.UpdateText("Invalid player name");
			}
			else {
				okGameName = true;
				inputStatus.UpdateText("Save game succesfully!");
				inputStatus.SetTextColor(8);
			}
		}
		else if (game->inputHandle->keyState_[Keyboard::ESCAPE_KEY].isPressed) {
			return { "", "" };
		}
		else for (int i = 0; i < keyNumber; i++) {
			// input information from keyboard
			if (inputIndex == 0) {
				if (game->inputHandle->keyState_[i].isPressed) {
					game->sound->playEffectSound(int(Sound::Effect::TYPING));
					if (i == Keyboard::BACKSPACE_KEY) {
						if (playerName.size() > 0) {
							playerName.pop_back();
						}

						if (playerName.size() == 0) {
							playerName = " ";
						}
					}
					else if ((i >= Keyboard::A_KEY && i <= Keyboard::Z_KEY) ||
						(i >= Keyboard::a_KEY && i <= Keyboard::z_KEY) ||
						(i >= Keyboard::NUM_0_KEY && i <= Keyboard::NUM_9_KEY) ||
						i == Keyboard::SPACE_KEY
						) {
						if (playerName == " ") {
							playerName = "";
						}

						if (playerName.size() < 11) {
							playerName.push_back(i);
						}
					}
				}
			}
			else {
				if (game->inputHandle->keyState_[i].isPressed) {
					game->sound->playEffectSound(int(Sound::Effect::TYPING));
					if (i == Keyboard::BACKSPACE_KEY) {
						if (gameName.size() > 0) {
							gameName.pop_back();
						}

						if (gameName.size() == 0) {
							gameName = " ";
						}
					}
					else if ((i >= Keyboard::A_KEY && i <= Keyboard::Z_KEY) ||
						(i >= Keyboard::a_KEY && i <= Keyboard::z_KEY) ||
						(i >= Keyboard::NUM_0_KEY && i <= Keyboard::NUM_9_KEY) ||
						i == Keyboard::SPACE_KEY
						) {
						if (gameName == " ") {
							gameName = "";
						}

						if (gameName.size() < 11) {
							gameName.push_back(i);
						}
					}
				}
			}
		}

		// update input text
		game->ClearConsole();
		game->RenderSprite(bg, { 0, 0 });
		inputText1.UpdateText(playerName);
		inputText2.UpdateText(gameName);
		inputText1.Render();
		inputText2.Render();
		title1.Render();
		title2.Render();
		rule.Render();
		note.Render();
		inputStatus.Render();
		COORD cursorPos = inputIndex == 0 ? COORD(100, 63) : COORD(100, 73);
		game->RenderSprite(cursor, cursorPos);
		game->UpdateConsole();
	}

	return { playerName, gameName };
}

void GameMap::LoadSavedLanes()
{
	grasslane = Graphic::Sprite(DrawableRes::GrassLane, Overlapped::LAND);
	waterlane = Graphic::Sprite(DrawableRes::WaterLane, Overlapped::LAND);
	roadlane = Graphic::Sprite(DrawableRes::RoadLane, Overlapped::LAND);
	snowlane = Graphic::Sprite(DrawableRes::SnowLane, Overlapped::LAND);
	railwaylane = Graphic::Sprite(DrawableRes::RailWayLane, Overlapped::LAND);
	roadMarking = Graphic::Sprite(DrawableRes::RoadMarking, Overlapped::DECORATOR);

	for (int i = 0; i < gameInfo.lanesInfo.size(); i++) {
		auto lane = gameInfo.lanesInfo[i];

		switch (lane.laneType) {
		case LaneType::GRASS: {
			GrassLane* grassLane = new GrassLane(lane.lanePos, game, grasslane, lane);
			lanes.push_back(grassLane);
			break;
		}

		case LaneType::ROAD: {			
			RoadLane* roadLane = new RoadLane(lane.lanePos, game, roadlane, lane, false);
			lanes.push_back(roadLane);
			break;
		}

		case LaneType::WATER: {
			WaterLane* waterLane = new WaterLane(lane.lanePos, game, waterlane, lane);
			lanes.push_back(waterLane);
			break;
		}

		case LaneType::SNOW: {
			SnowLane* snowLane = new SnowLane(lane.lanePos, game, snowlane, lane);
			lanes.push_back(snowLane);
			break;
		}

		case LaneType::RAILWAY: {
			RailWayLane* railWayLane = new RailWayLane(lane.lanePos, game, railwaylane, lane);
			lanes.push_back(railWayLane);
			break;
		}

		}
	}

	// set road marking
	for (int i = 0; i < lanes.size() - 1; i++) {
		if (lanes[i]->laneType == LaneType::ROAD && lanes[i+1]->laneType == LaneType::ROAD) {
			RoadLane* roadLane = dynamic_cast<RoadLane*>(lanes[i+1]);
			roadLane->hasRoadMarking = true;
		}
	}
}

Log GameMap::GetLogByLaneId(int laneId) {
	if (laneId >= 0 && laneId < lanes.size()) {
		WaterLane* lane = dynamic_cast<WaterLane*>(lanes[laneId]);

		return lane->GetLog();
	}

	return Log();
}

GameMapInfo GameMap::GetGameMapInfo(
	GameMapInfo partialInfo,
	GamePlayer* player,
	std::vector<Lane*> lanes
) {
	GameMapInfo gameInfo = partialInfo;

	// get player informations
	for (int i = 0; i < player->name.size(); i++) {
		gameInfo.playerInfo.playerName[i] = player->name[i];
	}
	gameInfo.playerInfo.playerType = player->playerType;
	gameInfo.playerInfo.moveDirec = player->movingDirection;
	gameInfo.playerInfo.aniState = player->animationState;
	gameInfo.playerInfo.lanePos = player->lanePos;
	gameInfo.playerInfo.position = player->getPosition();

	// get portal informations
	gameInfo.portalInfo = PortalInfo(
		portal.visible,
		portal.lanePos,
		portal.getPosition()
	);

	// get lane informations
	for (auto lane : lanes) {
		LaneInfo laneInfo;

		// switch case
		switch (lane->getObjType())
		{

		case ObjectType::GRASS_LANE: {
			GrassLane* grassLane = dynamic_cast<GrassLane*>(lane);
			laneInfo.lanePos = grassLane->id;
			laneInfo.laneType = LaneType::GRASS;
			laneInfo.objectDirection = MovingDirection::NONE;

			// get objects on grass lane 
			for (auto tree : grassLane->GetTrees()) {
				ObjectInfo objInfo;
				objInfo.objType = tree.getObjType();
				objInfo.speed = 0;
				objInfo.position = tree.getPosition();

				laneInfo.objectsInfo.push_back(objInfo);
			}

			for (auto rock : grassLane->GetRocks()) {
				ObjectInfo objInfo;
				objInfo.objType = rock.getObjType();
				objInfo.speed = 0;
				objInfo.position = rock.getPosition();

				laneInfo.objectsInfo.push_back(objInfo);
			}

			break;
		}

		case ObjectType::ROAD_LANE: {
			RoadLane* roadLane = dynamic_cast<RoadLane*>(lane);
			Vehicle _vehicle = roadLane->GetVehicle();
			laneInfo.lanePos = roadLane->id;
			laneInfo.laneType = LaneType::ROAD;
			laneInfo.objectDirection = _vehicle.movingDirection;

			// get objects on road lane 
			ObjectInfo vehicleInfo;
			vehicleInfo.objType = _vehicle.getObjType();
			vehicleInfo.speed = _vehicle.vehicleSpeed;
			vehicleInfo.position = _vehicle.getPosition();

			ObjectInfo coinInfo;
			coinInfo.objType = roadLane->coin.getObjType();
			coinInfo.speed = 0;
			coinInfo.position = roadLane->coin.getPosition();

			laneInfo.objectsInfo.push_back(vehicleInfo);
			laneInfo.objectsInfo.push_back(coinInfo);

			break;
		}


		case ObjectType::WATER_LANE: {
			WaterLane* waterLane = dynamic_cast<WaterLane*>(lane);
			laneInfo.lanePos = waterLane->id;
			laneInfo.laneType = LaneType::WATER;
			laneInfo.objectDirection = waterLane->direction;

			// get objects on water lane 
			ObjectInfo logInfo;
			Log _log = waterLane->GetLog();
			logInfo.objType = _log.getObjType();
			logInfo.speed = _log.logSpeed;
			logInfo.position = _log.getPosition();

			laneInfo.objectsInfo.push_back(logInfo);

			break;
		}

		case ObjectType::SNOW_LANE: {
			SnowLane* snowlane = dynamic_cast<SnowLane*>(lane);
			laneInfo.lanePos = snowlane->id;
			laneInfo.laneType = LaneType::SNOW;
			laneInfo.objectDirection = MovingDirection::NONE;

			// get objects on grass lane 
			for (auto tree : snowlane->GetTrees()) {
				ObjectInfo objInfo;
				objInfo.objType = tree.getObjType();
				objInfo.speed = 0;
				objInfo.position = tree.getPosition();

				laneInfo.objectsInfo.push_back(objInfo);
			}

			for (auto rock : snowlane->GetRocks()) {
				ObjectInfo objInfo;
				objInfo.objType = rock.getObjType();
				objInfo.speed = 0;
				objInfo.position = rock.getPosition();

				laneInfo.objectsInfo.push_back(objInfo);
			}

			break;
		}

		case ObjectType::RAILWAY_LANE: {
			RailWayLane* railWayLane = dynamic_cast<RailWayLane*>(lane);
			laneInfo.lanePos = railWayLane->id;
			laneInfo.laneType = LaneType::RAILWAY;
			laneInfo.objectDirection = MovingDirection::LEFT;

			// get train
			ObjectInfo trainInfo;
			Vehicle _train = railWayLane->GetVehicle();
			trainInfo.objType = _train.getObjType();
			trainInfo.speed = _train.vehicleSpeed;
			trainInfo.position = _train.getPosition();

			laneInfo.objectsInfo.push_back(trainInfo);

			break;
		}

		}

		gameInfo.lanesInfo.push_back(laneInfo);
	}

	return gameInfo;
}


