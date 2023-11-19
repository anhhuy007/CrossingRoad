#include "Log.h"

Log::Log(
	CrossingRoad* game,
	int _id,
	MovingDirection _direction
) : GameObject(game) {
	int random = rand() % 2;

	if (random) {
		logSprite = Graphic::Sprite(DrawableRes::Log1);
	}
	else {
		logSprite = Graphic::Sprite(DrawableRes::Log2);
	}

	lanePos = _id;
	setInitPosition();
	movingDirection = _direction;
	axisSpeed = GameSpeed(4, 1, 0, 0);
	logSpeed = float((rand() % 3) + 1) * 0.004;
	width = logSprite.getWidth();
	height = logSprite.getHeight();
	logSprite.SetOverlapped(Overlapped::LOG);
}

void Log::Update(float elapsedTime) {
	time += (elapsedTime / 10000);

	if (time > logSpeed) {
		if (movingDirection == MovingDirection::LEFT) {
			position.X -= axisSpeed.X_HORIZONTAL;
			position.Y -= axisSpeed.Y_HORIZONTAL;

			if (position.X + width < 0) {
				endOfRoad = true;
			}
		}
		else if (movingDirection == MovingDirection::RIGHT) {
			position.X += axisSpeed.X_HORIZONTAL;
			position.Y += axisSpeed.Y_HORIZONTAL;

			if (position.X > game->windowSize.x) {
				endOfRoad = true;
			}
		}

		time = 0;
	}
}

void Log::setSprite(Graphic::Sprite _sprite) {
	// delete old sprite
	width = _sprite.getWidth();
	height = _sprite.getHeight();
	logSprite = _sprite;
}

void Log::setInitPosition() {
	int blockPos = movingDirection == MovingDirection::LEFT ? 17 : 0;
	position = Alignment::getAlignedPosition(lanePos, blockPos, { 3, 15 }, Gravity::LEFT_CENTER);
}

