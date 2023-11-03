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
	this->player = new GamePlayer("Truck.sprite", { 100, 100 }, Overlapped::PLAYER, this->game);
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
	for (int i = 0; i < lanes.size(); i++) {
		lanes[i]->Render();
	}
}
