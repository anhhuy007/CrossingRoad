#include "GamePlayer.h"

void GamePlayer::Render() {
	// get appropriate sprite by animation state: normal, left, right, back, jump
	Graphic::Sprite sprite = getSpriteByAnimation(animationState);

	// render sprite
	game->RenderSprite(sprite, position);
}

Graphic::Sprite GamePlayer::getSpriteByAnimation(AnimationState state) {
	/*for (auto sprite : sprites) {
		if (sprite.first == state) {
			return sprite.second;
		}
	}

	return Graphic::Sprite();*/

	return sprite;
}

void GamePlayer::Update(float elapsedTime) {
	if (game->inputHandle.arrKeyState[Keyboard::UP_KEY].isPressed) {
		Graphic::gotoXY(1, 1);
		cout << "UP_KEY";
		if (this->moveUp()) {		// if GamePlayer can move up
			movingDirection = MovingDirection::UP;
			position.Y -= speed.Y_AXIS;
			OnMove();
		}
	}
	if (game->inputHandle.arrKeyState[Keyboard::DOWN_KEY].isPressed) {
		if (this->moveDown()) {		// if GamePlayer can move down
			Graphic::gotoXY(1, 1);
			cout << "DOWN_KEY";
			movingDirection = MovingDirection::DOWN;
			position.Y += speed.Y_AXIS;
			OnMove();
		}
	}
	if (game->inputHandle.arrKeyState[Keyboard::LEFT_KEY].isPressed) {
		if (this->moveLeft()) {		// if GamePlayer can move left
			movingDirection = MovingDirection::LEFT;
			position.X -= speed.X_AXIS;
			OnMove();
		}
	}
	if (game->inputHandle.arrKeyState[Keyboard::RIGHT_KEY].isPressed) {
		if (this->moveRight()) {	// if GamePlayer can move right
			movingDirection = MovingDirection::RIGHT;
			position.X += speed.X_AXIS;
			OnMove();
		}
	}
}

void GamePlayer::OnMove() {
	isAnimated = true;

	/*animationState = AnimationState::JUMP;
	Render();*/

	isAnimated = false;
}

bool GamePlayer::moveUp() {
	if (position.Y <= GameScreenLimit::TOP) return false;

	// check obstacle ahead
	// if (appearObstacle(position.X, position.Y - 1) return false;

	return true;
}

bool GamePlayer::moveDown() {
	if (position.Y >= GameScreenLimit::BOTTOM) return false;

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
	if (position.X >= GameScreenLimit::RIGHT) return false;

	// check obstacle ahead
	// if (appearObstacle(position.X + 1, position.Y) return false;

	return true;
}