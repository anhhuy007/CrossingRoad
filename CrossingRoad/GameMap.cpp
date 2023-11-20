#include "GameMap.h"
#include "WaterLane.h"

bool GameMap::OnCreate() {
	std::vector<AnimationSprite> spriteList;
	player = new GamePlayer(Player::CHICK, this->game);

	this->grid = Graphic::Sprite("sprites//Grid.sprite");
	grid.SetOverlapped(Overlapped::PLAYER);
	
	// create game lanes
	CreateLanes();
	SetScreenColor();
	
	return true;
}

bool GameMap::OnUpdate(float elapsedTime) {
	totalTime += elapsedTime;

	for (int i = 0; i < lanes.size(); i++) {
		lanes[i]->Update(elapsedTime);
	}
	player->Update(elapsedTime);

	/*if (player->lanePos == 8) {
		ScrollUp();
		player->lanePos += 1;
	}*/
	HandlePlayerCollision(elapsedTime);
	Render();

	return true;
}

void GameMap::Render() {
	game->RenderSprite(grid, {0, 0});

	for (int i = 0; i < lanes.size(); i++) {
		lanes[i]->Render();
		if (player->lanePos == i) player->Render();
	}
}

void GameMap::HandlePlayerCollision(float elapsedTime) {
	int collisType = player->CheckCollision();

	COORD pos = player->getPosition();

	if (collisType == 5) {
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
}

Log GameMap::GetLogByLaneId(int laneId) {
	if (laneId >= 0 && laneId < lanes.size()) {
		WaterLane* lane = dynamic_cast<WaterLane*>(lanes[laneId]);

		return lane->log;
	}

	return Log();
}
