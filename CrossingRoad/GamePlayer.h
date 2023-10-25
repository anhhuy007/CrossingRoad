#pragma once

#ifndef GAME_PLAYER_H
#define GAME_PLAYER_H

// ----- STANDARD LIB INCLUDES -----
#include <vector>
#include <iostream>

// ----- MY CLASS INCLUDES -----
#include "Values.h"
#include "GameObject.h";
#include "Graphic.h"

class GamePlayer : public GameObject {

	Graphic::Sprite getSpriteByAnimation(AnimationState state);

public:
	GamePlayer(
		const COORD& coord,
		const int& width,
		const int& height,
		CrossingRoad* game
	) : GameObject(width, height, coord, game) {}

	virtual void Update(float elapsedTime);
	virtual void Render();
	
	void OnMove();

	bool moveUp();
	bool moveDown();
	bool moveLeft();
	bool moveRight();

	short getX() { return position.X; }
	short getY() { return position.Y; }

protected:
	AnimationState animationState = AnimationState::NORMAL;
	MovingDirection movingDirection = MovingDirection::NONE;
	PlayerState state = PlayerState::STATE_ALIVE;
	std::vector<pair<AnimationState, Graphic::Sprite>> sprites;
	bool isAnimated = false;

	/*virtual void OnDied();
	virtual void Move(int x, int y) final;*/
};

#endif // !GAME_PLAYER_H