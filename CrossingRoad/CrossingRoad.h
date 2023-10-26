#pragma once

#ifndef _CROSSINGROAD_H_
#define _CROSSINGROAD_H_

#include "GameEngine.h"

class CrossingRoad : public GameEngine {	
public: 
	CrossingRoad() : GameEngine() {};
	
	class GameState {
	protected:
		CrossingRoad* game = nullptr;

	public:
		GameState(CrossingRoad* game) {
			this->game = game;
		}
		GameState() = default;

		virtual bool Update(float elapsedTime) { return true; }
		virtual bool Create() { return true; }
		virtual bool Exit() { return true; }
	};

	void SetState(GameState* state) {
		if (this->gameState != nullptr) {
			this->gameState->Exit();
		}
		this->gameState = state;
		this->gameState->Create();
	}

	GameState* gameState = nullptr;
	void Init();
	virtual bool GameCreate();
	virtual bool GameUpdate(float elapsedTime);
};

#endif // !_CROSSINGROAD_H_