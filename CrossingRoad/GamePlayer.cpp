#include "GamePlayer.h"
#include <iostream>

GamePlayer::GamePlayer(
	Player player,
	CrossingRoad* game
) : GameObject({ 0, 0 }, game) {
	// initial player position
	lanePos = 14;
	blockPos = 5;
	position = { 31, 217 };
	// get the animation sprites
	animationSprite = Factory::GetPlayerSprite(player);
	speed = GameSpeed(24, 6, -11, 21);
	axisSpeed = GameSpeed(4, 1, -1, 2);
	OnMove();

	// set collision points
	setCollisionPoints(
		Factory::GetObjectCollisionPoints(ObjectType::PLAYER)
	);
}

void GamePlayer::Render() {
	// get appropriate sprite by animation state: normal, left, right, back, jump
	Graphic::Sprite sprite = GetSpriteByAnimation(animationState);

	// render sprite
	game->RenderSprite(sprite, position);
}

Graphic::Sprite GamePlayer::GetSpriteByAnimation(AnimationState state) {
	for (auto playerSprite : animationSprite) {
		if (playerSprite.state == state) {
			return playerSprite.sprite;
		}
	}

	return animationSprite[0].sprite;
}

void GamePlayer::Update(float elapsedTime) {
	if (animationState == AnimationState::DEAD ||
		animationState == AnimationState::DROWN) return;

	if (game->inputHandle->keyState_[Keyboard::UP_KEY].isPressed) {
		if (CheckMoveUp()) {		// if GamePlayer can move up
			movingDirection = MovingDirection::UP;
			animationState = AnimationState::NORMAL;

			// animation
			OnMove();
		}
	}
	if (game->inputHandle->keyState_[Keyboard::DOWN_KEY].isPressed) {
		if (CheckMoveDown()) {		// if GamePlayer can move down
			movingDirection = MovingDirection::DOWN;
			animationState = AnimationState::TURN_BACK;

			// animation
			OnMove();
		}
	}
	if (game->inputHandle->keyState_[Keyboard::LEFT_KEY].isPressed) {
		if (CheckMoveLeft()) {		// if GamePlayer can move left
			movingDirection = MovingDirection::LEFT;
			animationState = AnimationState::TURN_LEFT;

			// animation
			OnMove();
		}
	}
	if (game->inputHandle->keyState_[Keyboard::RIGHT_KEY].isPressed) {
		if (CheckMoveRight()) {	// if GamePlayer can move right
			movingDirection = MovingDirection::RIGHT;
			animationState = AnimationState::TURN_RIGHT;

			// animation
			OnMove();
		}
	}
}

void GamePlayer::OnMove() {
	switch (movingDirection) {
	case MovingDirection::UP:
		position.X -= speed.X_VERTICAL;
		position.Y -= speed.Y_VERTICAL;
		if (lanePos % 3 == 1) {
			position.X -= 1;
			position.Y -= 1;
		}
		lanePos -= 1;

		break;

	case MovingDirection::LEFT:
		position.X -= speed.X_HORIZONTAL;
		position.Y -= speed.Y_HORIZONTAL;
		blockPos -= 1;

		break;

	case MovingDirection::RIGHT:
		position.X += speed.X_HORIZONTAL;
		position.Y += speed.Y_HORIZONTAL;
		blockPos += 1;

		break;

	case MovingDirection::DOWN:
		position.X += speed.X_VERTICAL;
		position.Y += speed.Y_VERTICAL;
		if (lanePos % 3 == 0) {
			position.X += 1;
			position.Y += 1;
		}
		lanePos += 1;

		break;
	}
}

bool GamePlayer::CheckMoveUp() {
	movingDirection = MovingDirection::UP;

	OnMove();
	int check = CheckCollision();
	bool validPos = ValidPosition();

	movingDirection = MovingDirection::DOWN;
	OnMove();

	return (check != 3 && validPos);
}

bool GamePlayer::CheckMoveDown() {
	movingDirection = MovingDirection::DOWN;

	OnMove();
	int check = CheckCollision();
	bool validPos = ValidPosition();

	movingDirection = MovingDirection::UP;
	OnMove();

	return (check != 3 && validPos);
}

bool GamePlayer::CheckMoveLeft() {
	movingDirection = MovingDirection::LEFT;
	OnMove();

	int check = CheckCollision();
	bool validPos = ValidPosition();

	movingDirection = MovingDirection::RIGHT;
	OnMove();

	return (check != 3 && validPos);
}

bool GamePlayer::CheckMoveRight() {
	movingDirection = MovingDirection::RIGHT;
	OnMove();

	int check = CheckCollision();
	bool validPos = ValidPosition();

	movingDirection = MovingDirection::LEFT;
	OnMove();

	return (check != 3 && validPos);
}

bool GamePlayer::ValidPosition() {
	return (position.X >= GameScreenLimit::LEFT &&
			position.X + width <= GameScreenLimit::RIGHT &&
			position.Y >= GameScreenLimit::TOP &&
			position.Y + height <= GameScreenLimit::BOTTOM
		);
}

int GamePlayer::CheckCollision() {
	/* COLLISSION VALUES:
		0: no collision
		1: player
		2: item
		3: tree, rock, bush
		4: car, truck, water
		5: floating object */
	int collisType = 0;

	for (auto point : collisionPoints) {
		point.first = {
			short(point.first.X + position.X),
			short(point.first.Y + position.Y)
		};

		int temp = game->CheckCollisionPoint(point.first);
		collisType = max(collisType, temp);
	}

	return collisType;
}

void GamePlayer::MoveHorizontal(
	float elapsedTime, 
	float timeSpeed, 
	MovingDirection direction
) {
	totalTime += (elapsedTime / 10000);

	if (totalTime > timeSpeed) {
		if (!ValidPosition()) {
			animationState = AnimationState::DROWN;
			return;
		}

		totalTime = 0;
		switch (direction) {
		case MovingDirection::LEFT:
			position.X -= axisSpeed.X_HORIZONTAL;
			position.Y -= axisSpeed.Y_HORIZONTAL;

			break;
		case MovingDirection::RIGHT:
			position.X += axisSpeed.X_HORIZONTAL;
			position.Y += axisSpeed.Y_HORIZONTAL;

			break;
		}
	}
}
