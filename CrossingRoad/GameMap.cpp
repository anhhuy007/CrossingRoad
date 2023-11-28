#include "GameMap.h"
#include "WaterLane.h"
#include "RoadLane.h"
#include "WinterMap.h"

bool GameMap::OnCreate() {
	if (gameInfo != nullptr) {
		level = gameInfo->level + 1;
		collectedCoins = gameInfo->collectedCoins;
	}

	player = new GamePlayer(Player::DUCKY, game);
	portal = Portal(game);
	grid = Graphic::Sprite(DrawableRes::Grid, Overlapped::PLAYER);
	
	// widgets
	std::vector<Widget::Button> buttons = {
		Widget::Button(
			game,
			"Exit",
			[]() {}
		),
		Widget::Button(
			game,
			"Save game",
			[]() {}
		),
		Widget::Button(
			game,
			"Continue",
			[]() {}
		),
	};
	dialog = Widget::Dialog(
		game,
		"Choose your option",
		buttons,
		{ 100, 50 },
		100,
		100
	);
	
	// create game lanes
	CreateLanes();
	SetScreenColor();

	maxIndex = 14;
	
	return true;
}

bool GameMap::OnUpdate(float elapsedTime) {
	if (!isPaused) {
		totalTime += elapsedTime;

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
			score++;
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
	// display dialog to ask player to continue or exit game
	isPaused = true;
	dialog.Update(30);
	dialog.Render();

	// if player press ESC, exit game
	if (game->inputHandle->keyState_[Keyboard::SPACE_KEY].isPressed) {
		CrossingRoad::Navigation::To(new MenuScreen(game));
		return true;
	}

	// if player press ENTER, continue game
	if (game->inputHandle->keyState_[Keyboard::ENTER_KEY].isPressed) {
		isPaused = false;
	}

	return true;
}

void GameMap::CreateNewGameLevel(LevelInformation* levelInfo) {
	
	if (levelInfo != nullptr) {
		// reset game properties
		level = levelInfo->level;
		score = levelInfo->score;
		collectedCoins = levelInfo->collectedCoins;
		totalTime = levelInfo->totalTime;
		endlessMode = levelInfo->endlessMode;
	}

	OnCreate();
}

void GameMap::Render() {
	for (int i = 0; i < lanes.size(); i++) {
		if (portal.lanePos == i) portal.Render();
		lanes[i]->Render();
		if (player->lanePos == i) player->Render();
	}

	// update text 
	std::string str_score = std::to_string(score);
	std::string str_coin = std::to_string(collectedCoins);

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
		system("pause");

		// get current level information
		LevelInformation levelInfo;
		levelInfo.level = level;
		levelInfo.score = score;
		levelInfo.collectedCoins = collectedCoins;
		levelInfo.totalTime = totalTime;
		levelInfo.endlessMode = endlessMode;

		CrossingRoad::Navigation::To(new WinterMap(game));
	}
	else if (collisType == 2) {
		// player hit the coin
		//Sound::playEffectSound(game->soundSetting, int(Sound::Effect::COIN));
		collectedCoins++;
		RoadLane* lane = dynamic_cast<RoadLane*>(lanes[player->lanePos + 1]);
		lane->coin.isCollected = true;
	}

	return true;
}

Log GameMap::GetLogByLaneId(int laneId) {
	if (laneId >= 0 && laneId < lanes.size()) {
		WaterLane* lane = dynamic_cast<WaterLane*>(lanes[laneId]);

		return lane->log;
	}

	return Log();
}
