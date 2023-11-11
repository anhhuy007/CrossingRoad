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

	Graphic::Sprite getSpriteByAnimation(AnimationState state);

public:
	GamePlayer(
		Player player, 
		CrossingRoad* game
	);

	virtual void Update(float elapsedTime);
	virtual void Render();
	
	void OnMove();

	bool moveUp();
	bool moveDown();
	bool moveLeft();
	bool moveRight();

	short getX() { return position.X; }
	short getY() { return position.Y; }

	int lanePos;
	int blockPos;

protected:
	AnimationState animationState = AnimationState::NORMAL;
	MovingDirection movingDirection = MovingDirection::UP;
	PlayerState state = PlayerState::STATE_ALIVE;
	vector<AnimationSprite> animationSprite;
	bool isAnimated = false;
	GameSpeed speed;
	
	/*virtual void OnDied();*/
};

#endif // !GAME_PLAYER_H