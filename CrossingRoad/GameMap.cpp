#include "GameMap.h"

GameMap::GameMap() {
	level = 0;
	score = 0;
	collectedCoins = 0;
	playerIndex = 0;
	totalTime = 0.0;
	player = nullptr;
}

GameMap::GameMap(CrossingRoad* game) : GameState(game) {
	level = 0;
	score = 0;
	collectedCoins = 0;
	playerIndex = 0;
	totalTime = 0.0;
	nullptr;
}

bool GameMap::Create() {
	// create new player
	vector<AnimationSprite> spriteList;
	//player = new GamePlayer(Player::CHICKCHUK, this->game);
	//this->grid = Graphic::Sprite("Grid.sprite");
	grid.setOverlapped(Overlapped::PLAYER);
	CreateLanes();
	
	return true;
}

bool GameMap::Update(float elapsedTime) {
	totalTime += elapsedTime;

	//player->Update(elapsedTime);
	for (int i = 0; i < lanes.size(); i++) {
		lanes[i]->Update(elapsedTime);
	}
	Render();

	return true;
}

void GameMap::Render() {
	game->RenderSprite(grid, {0, 0});
	for (int i = 0; i < lanes.size(); i++) {
		lanes[i]->Render();
		//if (player->lanePos == i) player->Render();
	}
}
