#include "GameMap.h"
#include "WaterLane.h"
#include "RoadLane.h"

bool GameMap::OnCreate() {
	player = new GamePlayer(Player::CHICK, game);
	portal = Portal(game);
	grid = Graphic::Sprite(DrawableRes::Grid, Overlapped::PLAYER);
	
	// create game lanes
	CreateLanes();
	SetScreenColor();

	maxIndex = 14;
	
	return true;
}

bool GameMap::OnUpdate(float elapsedTime) {
	totalTime += elapsedTime;

	// update lanes and player position
	for (int i = 0; i < lanes.size(); i++) {
		lanes[i]->Update(elapsedTime);
	}

	// disable player moving above lane containing portal
	if (portal.lanePos != 9 || 
		player->lanePos != 7 || 
		!game->inputHandle->keyState_[Keyboard::UP_KEY].isPressed
	) {
		player->Update(elapsedTime);
	}

	// check for game collision
	if (portal.lanePos == 9) portal.WriteCollisionPoints();
	HandlePlayerCollision(elapsedTime);

	// update score
	int playerPos = player->lanePos;
	if (playerPos < maxIndex) {
		maxIndex = playerPos;
		score++;
	}

	// display game 
	Render();

	// handle map scrolling up
	if (playerPos == 6 && portal.lanePos != 9) {
		ScrollUp();
		player->MoveDown();
		portal.MoveDown();
		maxIndex++;
	}

	return true;
}

void GameMap::Render() {
	//game->RenderSprite(grid, {0, 0});
	//game->RenderSprite(portal, { 0, 0 });
	for (int i = 0; i < lanes.size(); i++) {
		if (portal.lanePos == i) portal.Render();
		lanes[i]->Render();
		if (player->lanePos == i) player->Render();
	}

	// display score
	std::string playerScore = std::to_string(score);
	Widget::Text textScore = Widget::Text(
		game,
		playerScore,
		{ 440, 7 },
		30, 30,
		TextFont::NORMAL
	);

	// display collected coins
	std::string playerCoins = std::to_string(collectedCoins);
	Widget::Text textCoins = Widget::Text(
		game,
		playerCoins,
		{ 440, 14 },
		30, 30,
		TextFont::NORMAL
	);

	textScore.Render();
	textCoins.Render();
}

void GameMap::HandlePlayerCollision(float elapsedTime) {
	int collisType = player->CheckCollision();

	COORD pos = player->getPosition();

	if (collisType == 5) {
		if (player->animationState == AnimationState::DROWN) return;

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
			//system("pause");
		}
		// player is hit by car
		else {
			player->animationState = AnimationState::DEAD;
		}
	}
	else if (collisType == 6) {
		// player hit the portal
		system("pause");
		CrossingRoad::Navigation::To(new MenuScreen(game));
	}
	else if (collisType == 2) {
		// player hit the coin
		Sound::playEffectSound(game->soundSetting, int(Sound::Effect::COIN));
		collectedCoins++;
		RoadLane* lane = dynamic_cast<RoadLane*>(lanes[player->lanePos + 1]);
		lane->coin.isCollected = true;
	}
}

Log GameMap::GetLogByLaneId(int laneId) {
	if (laneId >= 0 && laneId < lanes.size()) {
		WaterLane* lane = dynamic_cast<WaterLane*>(lanes[laneId]);

		return lane->log;
	}

	return Log();
}
