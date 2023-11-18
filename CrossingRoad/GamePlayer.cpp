#include "GamePlayer.h"

GamePlayer::GamePlayer(
	Player player,
	CrossingRoad* game
) : GameObject({ 0, 0 }, game) {
	// initial player position
	lanePos = 11;
	blockPos = 8;

	// get the animation sprites
	animationSprite = Factory::GetPlayerSprite(player);
	speed = GameSpeed(4, 1, -1, 2);
	OnMove();

	// set collision points
	setCollisionPoints(
		Factory::GetObjectCollisionPoints(ObjectType::PLAYER)
	);
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
		if (moveUp()) {		// if GamePlayer can move up
			movingDirection = MovingDirection::UP;
			animationState = AnimationState::NORMAL;
			position.X -= speed.X_VERTICAL;
			position.Y -= speed.Y_VERTICAL;
			lanePos -= 1;
			OnMove();
		}
	}
	if (game->inputHandle->keyState_[Keyboard::DOWN_KEY].isPressed) {
		if (moveDown()) {		// if GamePlayer can move down
			movingDirection = MovingDirection::DOWN;
			animationState = AnimationState::TURN_BACK;
			position.X += speed.X_VERTICAL;
			position.Y += speed.Y_VERTICAL;
			lanePos += 1;
			OnMove();
		}
	}
	if (game->inputHandle->keyState_[Keyboard::LEFT_KEY].isPressed) {
		if (moveLeft()) {		// if GamePlayer can move left
			movingDirection = MovingDirection::LEFT;
			animationState = AnimationState::TURN_LEFT;
			position.X -= speed.X_HORIZONTAL;
			position.Y -= speed.Y_HORIZONTAL;
			blockPos -= 1;
			OnMove();
		}
	}
	if (game->inputHandle->keyState_[Keyboard::RIGHT_KEY].isPressed) {
		if (moveRight()) {	// if GamePlayer can move right
			movingDirection = MovingDirection::RIGHT;
			animationState = AnimationState::TURN_RIGHT;
			position.X += speed.X_HORIZONTAL;
			position.Y += speed.Y_HORIZONTAL;
			blockPos += 1;
			OnMove();
		}
	}

	// update collision points
	WriteCollisionPoints();
}

void GamePlayer::OnMove() {
	position = Alignment::getAlignedPosition(
		lanePos, 
		blockPos, 
		{ 0, -2 }, 
		Gravity::CENTRALLY_ALIGNED
	);
	
	// get jumping direction
	/*AnimationState tempAnimation = animationState; 
	COORD tempPosition = position;*/

	//switch (movingDirection) {
	//case MovingDirection::UP:
	//	animationState = AnimationState::JUMP_AHEAD;
	//	//position.Y -= 10;
	//	break;

	//case MovingDirection::LEFT:
	//	animationState = AnimationState::JUMP_LEFT;
	//	break;

	//case MovingDirection::RIGHT:
	//	animationState = AnimationState::JUMP_RIGHT;
	//	break;

	//case MovingDirection::DOWN:
	//	animationState = AnimationState::JUMP_BACK;
	//	break;
	//}

	//Render();
	//animationState = tempAnimation;
	//position = tempPosition;
	Render();
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

bool GamePlayer::CheckCollision() {
	for (auto point : collisionPoints) {
		point.first = {
			short(point.first.X + position.X),
			short(point.first.Y + position.Y)
		};
		if (game->CheckCollisionPoint(point.first) == 2) {
			return true;
		}
	}

	return false;
}
