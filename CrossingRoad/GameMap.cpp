#include "GameMap.h"
#include "WaterLane.h"

bool GameMap::OnCreate() {
	player = new GamePlayer(Player::CHICK, game);
	//portal = Graphic::Sprite(DrawableRes::Portal, Overlapped::OBSTACLE);
	grid = Graphic::Sprite(DrawableRes::Grid, Overlapped::PLAYER);
	
	// create game lanes
	CreateLanes();
	SetScreenColor();

	maxIndex = 14;
	
	return true;
}

bool GameMap::OnUpdate(float elapsedTime) {
	totalTime += elapsedTime;

	for (int i = 0; i < lanes.size(); i++) {
		lanes[i]->Update(elapsedTime);
	}
	player->Update(elapsedTime);
	HandlePlayerCollision(elapsedTime);

	// update score
	int playerPos = player->lanePos;
	if (playerPos < maxIndex) {
		maxIndex = playerPos;
		score++;
	}

	// display game 
	Render();

	if (player->lanePos == 6) {
		ScrollUp();
		player->MoveDown();
		maxIndex++;
	}

	return true;
}

void GameMap::Render() {
	//game->RenderSprite(grid, {0, 0});
	//game->RenderSprite(portal, { 0, 0 });
	for (int i = 0; i < lanes.size(); i++) {
		lanes[i]->Render();
		if (player->lanePos == i) player->Render();
	}

	std::string playerScore = std::to_string(score);
	Widget::Text textScore = Widget::Text(
		game,
		playerScore,
		{ 440, 9 },
		30, 30,
		TextFont::NORMAL
	);

	textScore.Render();
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
}

Log GameMap::GetLogByLaneId(int laneId) {
	if (laneId >= 0 && laneId < lanes.size()) {
		WaterLane* lane = dynamic_cast<WaterLane*>(lanes[laneId]);

		return lane->log;
	}

	return Log();
}
