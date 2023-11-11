#include "GamePlayer.h"

GamePlayer::GamePlayer(
	Player player,
	CrossingRoad* game
) : GameObject({ 0, 0 }, game) {
	// initial player attributes
	lanePos = 11;
	blockPos = 8;

	// get the animation sprites
	animationSprite = Factory::GetAnimationSprite(player);
	for (auto& sprite : animationSprite) {
		sprite.sprite.setOverlapped(Overlapped::PLAYER);
	}

	OnMove();
}

void GamePlayer::Render() {
	// get appropriate sprite by animation state: normal, left, right, back, jump
	Graphic::Sprite sprite = getSpriteByAnimation(animationState);

	// render sprite
	game->RenderSprite(sprite, position);
}

Graphic::Sprite GamePlayer::getSpriteByAnimation(AnimationState state) {
	for (auto playerSprite : animationSprite) {
		if (playerSprite.state == state) {
			return playerSprite.sprite;
		}
	}

	return animationSprite[0].sprite;
}

void GamePlayer::Update(float elapsedTime) {
	if (game->inputHandle->keyState_[Keyboard::UP_KEY].isPressed) {
		Graphic::gotoXY(1, 1);
		if (this->moveUp()) {		// if GamePlayer can move up
			movingDirection = MovingDirection::UP;
			animationState = AnimationState::NORMAL;
			lanePos -= 1;
			OnMove();
		}
	}
	if (game->inputHandle->keyState_[Keyboard::DOWN_KEY].isPressed) {
		if (this->moveDown()) {		// if GamePlayer can move down
			Graphic::gotoXY(1, 1);
			movingDirection = MovingDirection::DOWN;
			animationState = AnimationState::TURN_BACK;
			lanePos += 1;
			OnMove();
		}
	}
	if (game->inputHandle->keyState_[Keyboard::LEFT_KEY].isPressed) {
		if (this->moveLeft()) {		// if GamePlayer can move left
			movingDirection = MovingDirection::LEFT;
			animationState = AnimationState::TURN_LEFT;
			blockPos -= 1;
			OnMove();
		}
	}
	if (game->inputHandle->keyState_[Keyboard::RIGHT_KEY].isPressed) {
		if (this->moveRight()) {	// if GamePlayer can move right
			movingDirection = MovingDirection::RIGHT;
			animationState = AnimationState::TURN_RIGHT;
			blockPos += 1;
			OnMove();
		}
	}
}

void GamePlayer::OnMove() {
	isAnimated = true;
	position = Alignment::getAlignedPosition(lanePos, blockPos, { 0, -2 }, Gravity::CENTRALLY_ALIGNED);
	
	// get jumping direction
	AnimationState tempAnimation = animationState; 
	COORD tempPosition = position;

	switch (movingDirection) {
	case MovingDirection::UP:
		animationState = AnimationState::JUMP_AHEAD;
		position.Y -= 10;
		break;

	case MovingDirection::LEFT:
		animationState = AnimationState::JUMP_LEFT;
		break;

	case MovingDirection::RIGHT:
		animationState = AnimationState::JUMP_RIGHT;
		break;

	case MovingDirection::DOWN:
		animationState = AnimationState::JUMP_BACK;
		break;
	}

	Render();
	animationState = tempAnimation;
	position = tempPosition;
	Render();

	isAnimated = false;
}

bool GamePlayer::moveUp() {
	if (position.Y <= GameScreenLimit::TOP) return false;

	// check obstacle ahead
	// if (appearObstacle(position.X, position.Y - 1) return false;

	return true;
}

bool GamePlayer::moveDown() {
	if (position.Y + height >= GameScreenLimit::BOTTOM) return false;

	// check obstacle ahead
	// if (appearObstacle(position.X, position.Y + 1) return false;

	return true;
}

bool GamePlayer::moveLeft() {
	if (position.X <= GameScreenLimit::LEFT) return false;

	// check obstacle ahead
	// if (appearObstacle(position.X - 1, position.Y) return false;

	return true;
}

bool GamePlayer::moveRight() {
	if (position.X + width >= GameScreenLimit::RIGHT) return false;

	// check obstacle ahead
	// if (appearObstacle(position.X + 1, position.Y) return false;

	return true;
}