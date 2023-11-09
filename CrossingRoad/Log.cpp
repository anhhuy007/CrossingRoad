#include "Log.h"

Log::Log(
	CrossingRoad* game,
	int _id,
	MovingDirection _direction
) : GameObject(game) {
	int random = rand() % 2;

	if (random) {
		logSprite = Graphic::Sprite("Log1.sprite");
	}
	else {
		logSprite = Graphic::Sprite("Log2.sprite");
	}

	id = _id;
	setInitPosition();
	movingDirection = _direction;
	axisSpeed = GameSpeed(4, 1, 0, 0);
	logSpeed = float((rand() % 3) + 1) * 0.004;
	width = logSprite.getWidth();
	height = logSprite.getHeight();
	logSprite.setOverlapped(Overlapped::OBSTACLE);
}

void Log::Update(float elapsedTime) {
	time += (elapsedTime / 100000000);

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

void Log::Render() {};

void Log::setSprite(Graphic::Sprite _sprite) {
	// delete old sprite
	width = _sprite.getWidth();
	height = _sprite.getHeight();
	logSprite = _sprite;
	overlapped = Overlapped::VEHICLE;
}

void Log::setInitPosition() {
	/*if (logType == LogType::SMALL_LOG) {
		position.X = movingDirection == MovingDirection::LEFT ? 460 : -10;
		position.Y = movingDirection == MovingDirection::LEFT ? id * 24 - 44 : id * 24 - 158;
	}
	else if (logType == LogType::BIG_LOG) {
		position.X = movingDirection == MovingDirection::LEFT ? 460 : -10;
		position.Y = movingDirection == MovingDirection::LEFT ? id * 24 - 56 : id * 24 - 170;
	}*/

	position = movingDirection == MovingDirection::LEFT
		? Alignment::getAlignedPosition(id, 17, { 3, 15 }, Gravity::LEFT_CENTER)
		: Alignment::getAlignedPosition(id, 0, { 3, 15 }, Gravity::LEFT_CENTER);
	/*cout << id << " " << position.X << " " << position.Y;
	system("pause");*/
}

