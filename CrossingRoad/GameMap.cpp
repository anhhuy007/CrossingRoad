#include "GameMap.h"

GameMap::GameMap() {
	this->level = 0;
	this->score = 0;
	this->collectedCoins = 0;
	this->playerIndex = 0;
	this->totalTime = 0.0;
	this->player = nullptr;
}

GameMap::GameMap(CrossingRoad* game) : GameState(game) {
	this->level = 0;
	this->score = 0;
	this->collectedCoins = 0;
	this->playerIndex = 0;
	this->totalTime = 0.0;
	this->player = nullptr;
}

bool GameMap::Create() {
	this->level = 1;
	this->score = 0;
	this->collectedCoins = 0;
	this->playerIndex = 0;
	this->totalTime = 0.0;

	// create new player
	this->player = new GamePlayer("Player.sprite", { 100, 100 }, Overlapped::VEHICLE, this->game);
	this->grid = Graphic::Sprite("Grid.sprite");
	grid.setOverlapped(Overlapped::PLAYER);
	CreateLanes();
	
	return true;
}

bool GameMap::Update(float elapsedTime) {
	totalTime += elapsedTime;

	player->Update(elapsedTime);
	for (int i = 0; i < lanes.size(); i++) {
		lanes[i]->Update(elapsedTime);
	}
	Render();

	return true;
}

void GameMap::Render() {
	player->Render();
	game->RenderSprite(grid, {0, 0});
	for (int i = 0; i < lanes.size(); i++) {
		lanes[i]->Render();
	}
}
