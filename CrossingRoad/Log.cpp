#include "Log.h"

Log::Log(
	CrossingRoad* game,
	int _id,
	MovingDirection _direction
) : GameObject(game) {
	int random = rand() % 2;

	if (random) {
		logSprite = Graphic::Sprite(DrawableRes::Log1);
		SetCollisionPoints(Factory::GetObjectCollisionPoints(ObjectType::SMALL_LOG));
		objType = ObjectType::SMALL_LOG;
	}
	else {
		logSprite = Graphic::Sprite(DrawableRes::Log2);
		SetCollisionPoints(Factory::GetObjectCollisionPoints(ObjectType::BIG_LOG));
		objType = ObjectType::BIG_LOG;
	}

	lanePos = _id;
	endOfRoad = true;
	movingDirection = _direction;
	axisSpeed = GameSpeed(4, 1, -11, 21);
	logSpeed = float((rand() % 3) + 1) * 0.004;
	width = logSprite.GetWidth();
	height = logSprite.GetHeight();
	logSprite.SetOverlapped(Overlapped::LOG);
}

Log::Log(
	CrossingRoad* game, 
	int _lanePos, 
	MovingDirection _direction, 
	ObjectInfo _info
) : GameObject(game)
{
	objType = _info.objType;
	lanePos = _lanePos;
	movingDirection = _direction;
	axisSpeed = GameSpeed(4, 1, -11, 21);
	logSpeed = _info.speed;
	position = _info.position;

	switch (objType) {
	case ObjectType::SMALL_LOG: {
		logSprite = Graphic::Sprite(DrawableRes::Log1);
		SetCollisionPoints(Factory::GetObjectCollisionPoints(ObjectType::SMALL_LOG));
		break;
	}

	case ObjectType::BIG_LOG: {
		logSprite = Graphic::Sprite(DrawableRes::Log2);
		SetCollisionPoints(Factory::GetObjectCollisionPoints(ObjectType::BIG_LOG));
		break;
	}

	}

	logSprite.SetOverlapped(Overlapped::LOG);
	width = logSprite.GetWidth();
	height = logSprite.GetHeight();
	logSprite.SetOverlapped(Overlapped::OBSTACLE);
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

	// update collision points
	WriteCollisionPoints();
}

void Log::SetSprite(Graphic::Sprite _sprite) {
	// delete old sprite
	width = _sprite.GetWidth();
	height = _sprite.GetHeight();
	logSprite = _sprite;
}

void Log::SetInitPosition() {
	int blockPos = movingDirection == MovingDirection::LEFT ? 17 : 0;
	position = Alignment::GetAlignedPosition(lanePos, blockPos, { 3, 15 }, Gravity::LEFT_CENTER);
}

