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
			[]() {}
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


Log GameMap::GetLogByLaneId(int laneId) {
	if (laneId >= 0 && laneId < lanes.size()) {
		WaterLane* lane = dynamic_cast<WaterLane*>(lanes[laneId]);

		return lane->log;
	}

	return Log();
}


