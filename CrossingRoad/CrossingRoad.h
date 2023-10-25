#pragma once

#ifndef _CROSSINGROAD_H_
#define _CROSSINGROAD_H_

#include "GameEngine.h"

class CrossingRoad : public GameEngine {	
public: 
	class GameState {
	protected:
		CrossingRoad* game = nullptr;

	public:
		GameState(CrossingRoad* game) {
			this->game = game;
		}
		GameState() = default;

		virtual bool Update(float elapsedTime) { return false; }
		virtual bool OnStateEnter() { return true; }
		virtual bool OnStateExit() { return true; }
	};

	void SetState(GameState* state) {
		if (this->gameState != nullptr) {
			this->gameState->OnStateExit();
		}
		this->gameState = state;
		this->gameState->OnStateEnter();
	}

	GameState* gameState = nullptr;
	void Init();
	virtual bool GameUpdate(float elapsedTime);
};

#endif // !_CROSSINGROAD_H_