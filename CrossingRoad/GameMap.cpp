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
	this->player = new GamePlayer("image.sprite", { 0, 0 }, OVERLLAPED::LAND, this->game);
	
	return true;
}

bool GameMap::Update(float elapsedTime) {
	totalTime += elapsedTime;

	/*Graphic::gotoXY(1, 1);
	cout << "GameUpdate: " << 1.0f / elapsedTime;*/

	player->Update(elapsedTime);
	Render();

	return true;
}

void GameMap::Render() {
	player->Render();
}
