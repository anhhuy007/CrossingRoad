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
	player = new GamePlayer(Player::DUCKY, game);
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
		30, 30,
		TextFont::NUMBER
	);

	// display collected coins
	Widget::Text textCoins = Widget::Text(
		game,
		str_coin,
		{ short(440 - str_coin.length() * 13 + 13), 22 },
		30, 30,
		TextFont::COIN_NUMBER
	);

	// display score
	textScore.Render();
	textCoins.Render();
	level.Render();
}

bool GameMap::HandlePlayerCollision(float elapsedTime) {
	int collisType = player->CheckCollision();

	COORD pos = player->getPosition();

	if (collisType == 5) {
		if (player->animationState == AnimationState::DROWN) return true;

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
		}
		// player is hit by car
		else {
			player->animationState = AnimationState::DEAD;
		}
	}
	else if (collisType == 6) {		
		// player hit the portal
		game->sound->turnOffBackgroundSound();

		// update game info for the next level
		gameInfo.score = 0;
		gameInfo.coin += 5; // add 5 coins for player
		gameInfo.level++;
		gameInfo.mapType = gameLevels[gameInfo.level - 1].first;
		gameInfo.endLane = gameLevels[gameInfo.level - 1].second;

		if (gameInfo.mapType == MapType::WINTER) {
			CrossingRoad::Navigation::To(new WinterMap(game, gameInfo));
		}
		else {
			CrossingRoad::Navigation::To(new ClassicMap(game, gameInfo));
		}

		system("pause");
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
	pausegame_dialog = Widget::Dialog(
		game,
		"Choose your option",
		buttons,
		{ 100, 50 },
		100,
		100
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
				CrossingRoad::Navigation::To(new WinterMap(game));
			}
		),
	};
	gameover_dialog = Widget::Dialog(
		game,
		"Game over",
		buttons2,
		{ 100, 50 },
		100,
		100
	);

	level = Widget::Text(
		game,
		std::to_string(gameInfo.level),
		{ 10, 5 },
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
	GameMapInfo finalInfo = GetGameMapInfo(gameInfo, player, lanes);
	bool status = FileIO::WriteGameInfo("test.game", finalInfo);

	if (status == true) {
		std::cout << "Game saved successfully" << std::endl;
	}
	else {
		std::cout << "Game saved failed" << std::endl;
	};

	system("pause");
}

void GameMap::LoadSavedLanes()
{
	grasslane = Graphic::Sprite(DrawableRes::GrassLane, Overlapped::LAND);
	waterlane = Graphic::Sprite(DrawableRes::WaterLane, Overlapped::LAND);
	roadlane = Graphic::Sprite(DrawableRes::RoadLane, Overlapped::LAND);
	snowlane = Graphic::Sprite(DrawableRes::SnowLane, Overlapped::LAND);
	roadMarking = Graphic::Sprite(DrawableRes::RoadMarking, Overlapped::DECORATOR);

	int cnt = 0;
	for (auto lane : gameInfo.lanesInfo) {
		switch (lane.laneType) {
		case LaneType::GRASS: {
			GrassLane* grassLane = new GrassLane(cnt, game, grasslane, lane);
			lanes.push_back(grassLane);
			break;
		}

		case LaneType::ROAD: {
			RoadLane* roadLane = new RoadLane(cnt, game, roadlane, lane);
			lanes.push_back(roadLane);
			break;
		}

		case LaneType::WATER: {
			WaterLane* waterLane = new WaterLane(cnt, game, waterlane, lane);
			lanes.push_back(waterLane);
			break;
		}

		case LaneType::SNOW: {
			SnowLane* snowLane = new SnowLane(cnt, game, snowlane, lane);
			lanes.push_back(snowLane);
			break;
		}

		}

		cnt++;
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
	gameInfo.playerInfo.moveDirec = player->movingDirection;
	gameInfo.playerInfo.aniState = player->animationState;
	gameInfo.playerInfo.lanePos = player->lanePos;
	gameInfo.playerInfo.position = player->getPosition();

	// get lane informations
	for (auto lane : lanes) {
		LaneInfo laneInfo;

		// switch case
		switch (lane->getObjType())
		{

		case ObjectType::GRASS_LANE: {
			GrassLane* grassLane = dynamic_cast<GrassLane*>(lane);
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
			laneInfo.laneType = LaneType::ROAD;
			Vehicle _vehicle = roadLane->GetVehicle();
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
			laneInfo.laneType = LaneType::WATER;
			laneInfo.objectDirection = MovingDirection::NONE;

			// get objects on water lane 
			ObjectInfo logInfo;
			Log _log = waterLane->GetLog();
			logInfo.objType = _log.getObjType();
			logInfo.speed = _log.logSpeed;
			logInfo.position = _log.getPosition();

			laneInfo.objectsInfo.push_back(logInfo);

			break;
		}

		case ObjectType::SNOW_LANE:
			SnowLane* snowlane = dynamic_cast<SnowLane*>(lane);
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

		gameInfo.lanesInfo.push_back(laneInfo);
	}

	return gameInfo;
}



