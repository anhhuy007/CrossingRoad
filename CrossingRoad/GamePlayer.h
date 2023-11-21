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
	MovingDirection movingDirection = MovingDirection::UP;
	std::vector<AnimationSprite> animationSprite;
	GameSpeed speed;
	GameSpeed axisSpeed;
	float totalTime = 0;

public:
	// attributes
	int lanePos;
	int blockPos;
	AnimationState animationState = AnimationState::NORMAL;

	// methods
	GamePlayer(
		Player player, 
		CrossingRoad* game
	);

	void Update(float elapsedTime);
	void Render();

	// moving functions
	void OnMove();
	void MoveHorizontal(
		float elapsedTime,
		float timeSpeed,
		MovingDirection direction
	);
	void MoveUp();	
	void MoveDown();
	void MoveLeft();
	void MoveRight();

	// check collision
	bool CheckMoveUp();
	bool CheckMoveDown();
	bool CheckMoveLeft();
	bool CheckMoveRight();
	bool ValidPosition();
	int CheckCollision();

	
};

#endif // !GAME_PLAYER_H