#include "Vehicle.h"

Vehicle::Vehicle(
	CrossingRoad* game, 
	int _id, 
	MovingDirection _direction
) : GameObject(game) {
	int random = rand() % 5;

	if (random == 0) {
		vehicleSprite = _direction == MovingDirection::LEFT
			? Graphic::Sprite(DrawableRes::Car1Left)
			: Graphic::Sprite(DrawableRes::Car1Right);

		// set collision points
		SetCollisionPoints(
			Factory::GetObjectCollisionPoints(ObjectType::GREEN_CAR)
		);
		objType = ObjectType::GREEN_CAR;
	}
	else if (random <= 2) {
		vehicleSprite = _direction == MovingDirection::LEFT
			? Graphic::Sprite(DrawableRes::Car2Left)
			: Graphic::Sprite(DrawableRes::Car2Right);

		// set collision points
		SetCollisionPoints(
			Factory::GetObjectCollisionPoints(ObjectType::RED_CAR)
		);
		objType = ObjectType::RED_CAR;
	}
	else {
		vehicleSprite = _direction == MovingDirection::LEFT
			? Graphic::Sprite(DrawableRes::TruckLeft)
			: Graphic::Sprite(DrawableRes::TruckRight);

		// set collision points
		SetCollisionPoints(
			Factory::GetObjectCollisionPoints(ObjectType::RED_TRUCK)
		);
		objType = ObjectType::RED_TRUCK;
	}

	endOfRoad = true;
	lanePos = _id;
	movingDirection = _direction;
	axisSpeed = GameSpeed(4, 1, -11, 21);
	vehicleSpeed = 0.001 + (rand() % 4 + 1) * 0.001;
	width = vehicleSprite.getWidth();
	height = vehicleSprite.getHeight();
	vehicleSprite.SetOverlapped(Overlapped::OBSTACLE);
}

Vehicle::Vehicle(
	CrossingRoad* game, 
	int _id, 
	MovingDirection _direction, 
	ObjectType _objType
) : GameObject(game)
{
	switch (_objType) {
	case ObjectType::RED_CAR:
		vehicleSprite = _direction == MovingDirection::LEFT
			? Graphic::Sprite(DrawableRes::Car1Left)
			: Graphic::Sprite(DrawableRes::Car1Right);

		SetCollisionPoints(Factory::GetObjectCollisionPoints(ObjectType::GREEN_CAR));
		break;

	case ObjectType::GREEN_CAR:
		vehicleSprite = _direction == MovingDirection::LEFT
			? Graphic::Sprite(DrawableRes::Car2Left)
			: Graphic::Sprite(DrawableRes::Car2Right);

		SetCollisionPoints(Factory::GetObjectCollisionPoints(ObjectType::RED_CAR));
		break;

	case ObjectType::RED_TRUCK:
		vehicleSprite = _direction == MovingDirection::LEFT
			? Graphic::Sprite(DrawableRes::TruckLeft)
			: Graphic::Sprite(DrawableRes::TruckRight);
		break;
		SetCollisionPoints(Factory::GetObjectCollisionPoints(ObjectType::RED_TRUCK));

	case ObjectType::TRAIN: 
		vehicleSprite = Graphic::Sprite(DrawableRes::Train);
		SetCollisionPoints(Factory::GetObjectCollisionPoints(ObjectType::TRAIN));
		
		// reset speed
		vehicleSpeed = 0;
		break;
	}

	objType = _objType;
	lanePos = _id;
	movingDirection = _direction;
	axisSpeed = GameSpeed(4, 1, -11, 21);
	vehicleSpeed = 0.001 + (rand() % 4 + 1) * 0.001;
	endOfRoad = true;
	width = vehicleSprite.getWidth();
	height = vehicleSprite.getHeight();
	vehicleSprite.SetOverlapped(Overlapped::OBSTACLE);
}

Vehicle::Vehicle(
	CrossingRoad* game, 
	int _lanePos,
	MovingDirection _direction, 
	ObjectInfo _info
) : GameObject(game)
{
	switch(_info.objType) {
		case ObjectType::RED_CAR:
			vehicleSprite = _direction == MovingDirection::LEFT
				? Graphic::Sprite(DrawableRes::Car1Left)
				: Graphic::Sprite(DrawableRes::Car1Right);
			SetCollisionPoints(Factory::GetObjectCollisionPoints(ObjectType::RED_CAR));
			break;

		case ObjectType::GREEN_CAR:
			vehicleSprite = _direction == MovingDirection::LEFT
				? Graphic::Sprite(DrawableRes::Car2Left)
				: Graphic::Sprite(DrawableRes::Car2Right);
			SetCollisionPoints(Factory::GetObjectCollisionPoints(ObjectType::GREEN_CAR));
			break;

		case ObjectType::RED_TRUCK:
			vehicleSprite = _direction == MovingDirection::LEFT
				? Graphic::Sprite(DrawableRes::TruckLeft)
				: Graphic::Sprite(DrawableRes::TruckRight);
			SetCollisionPoints(Factory::GetObjectCollisionPoints(ObjectType::RED_TRUCK));
			break;

		case ObjectType::TRAIN:
			vehicleSprite = Graphic::Sprite(DrawableRes::Train);
			SetCollisionPoints(Factory::GetObjectCollisionPoints(ObjectType::TRAIN));
			break;
	}

	objType = _info.objType;
	lanePos = _lanePos;
	movingDirection = _direction;
	axisSpeed = GameSpeed(4, 1, -11, 21);
	vehicleSpeed = _info.speed;
	position = _info.position;
	width = vehicleSprite.getWidth();
	height = vehicleSprite.getHeight();
	vehicleSprite.SetOverlapped(Overlapped::OBSTACLE);
}

void Vehicle::Update(float elapsedTime) {
	time += (elapsedTime / 10000);

	if (time > vehicleSpeed) {
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

void Vehicle::Render()
{
	if (!endOfRoad) game->RenderSprite(vehicleSprite, position);
}

void Vehicle::MoveAhead() {
	if (movingDirection == MovingDirection::LEFT) {
		position.X -= axisSpeed.X_HORIZONTAL;
		position.Y -= axisSpeed.Y_HORIZONTAL;
	}
	else {
		position.X += axisSpeed.X_HORIZONTAL;
		position.Y += axisSpeed.Y_HORIZONTAL;
	}
}

void Vehicle::SetInitPosition() {
	COORD centerSpot = { 0, 0 };
	int startBlock = movingDirection == MovingDirection::LEFT ? 19 : -5;

	switch (objType) {
	case ObjectType::GREEN_CAR:
	case ObjectType::RED_CAR:
		centerSpot = COORD(0, 20);
		break;
		
	case ObjectType::RED_TRUCK:
		centerSpot = COORD(0, 32);
		break;

	case ObjectType::TRAIN:
		centerSpot = COORD(0, 35);
		break;
	}

	position = Alignment::GetAlignedPosition(lanePos, startBlock, centerSpot, Gravity::TOP_LEFT);
}
