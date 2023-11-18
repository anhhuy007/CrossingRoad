#include "GameMap.h"

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

	player->Update(elapsedTime);
	for (int i = 0; i < lanes.size(); i++) {
		lanes[i]->Update(elapsedTime);
	}

	/*if (player->lanePos == 8) {
		ScrollUp();
		player->lanePos += 1;
	}*/

	Render();

	// check collision
	if (player->CheckCollision()) {
		system("pause");
	}

	return true;
}

void GameMap::Render() {
	game->RenderSprite(grid, {0, 0});

	player->Render();
	for (int i = 0; i < lanes.size(); i++) {
		lanes[i]->Render();
		if (player->lanePos == i) player->Render();
	}
}
