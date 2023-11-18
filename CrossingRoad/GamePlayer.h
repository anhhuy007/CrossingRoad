#pragma once

#ifndef GAME_PLAYER_H
#define GAME_PLAYER_H

#define X_AXIS first
#define Y_AXIS second

// ----- STANDARD LIB INCLUDES -----
#include <vector>
#include <iostream>

// ----- MY CLASS INCLUDES -----
#include "Values.h"
#include "GameObject.h";
#include "Graphic.h"
#include "Alignment.h"
#include "Factory.h"

class GamePlayer : public GameObject {
	// methods
	Graphic::Sprite getSpriteByAnimation(AnimationState state);

	// attributes
	AnimationState animationState = AnimationState::NORMAL;
	MovingDirection movingDirection = MovingDirection::UP;
	PlayerState state = PlayerState::STATE_ALIVE;
	std::vector<AnimationSprite> animationSprite;
	GameSpeed speed;
	float totalTime = 0;

public:
	// methods
	GamePlayer(
		Player player, 
		CrossingRoad* game
	);

	void Update(float elapsedTime);
	void Render();
	void OnMove();
	bool moveUp();
	bool moveDown();
	bool moveLeft();
	bool moveRight();

	bool CheckCollision();

	// attributes
	int lanePos;
	int blockPos;	
};

#endif // !GAME_PLAYER_H