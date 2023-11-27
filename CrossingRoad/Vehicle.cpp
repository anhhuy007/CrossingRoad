#include "Vehicle.h"

Vehicle::Vehicle(
	CrossingRoad* game, 
	int _id, 
	MovingDirection _direction
) : GameObject(game) {
	int random = rand() % 5;

	if (random == 0) {
		type = VehicleType::CAR;
		vehicleSprite = _direction == MovingDirection::LEFT
			? Graphic::Sprite(DrawableRes::Car1Left)
			: Graphic::Sprite(DrawableRes::Car1Right);

		// set collision points
		setCollisionPoints(
			Factory::GetObjectCollisionPoints(ObjectType::CAR)
		);
	}
	else if (random <= 2) {
		type = VehicleType::CAR;
		vehicleSprite = _direction == MovingDirection::LEFT
			? Graphic::Sprite(DrawableRes::Car2Left)
			: Graphic::Sprite(DrawableRes::Car2Right);

		// set collision points
		setCollisionPoints(
			Factory::GetObjectCollisionPoints(ObjectType::CAR)
		);
	}
	else {
		type = VehicleType::TRUCK;
		vehicleSprite = _direction == MovingDirection::LEFT
			? Graphic::Sprite(DrawableRes::TruckLeft)
			: Graphic::Sprite(DrawableRes::TruckRight);

		// set collision points
		setCollisionPoints(
			Factory::GetObjectCollisionPoints(ObjectType::TRUCK)
		);
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
	COORD centerSpot = type == VehicleType::CAR ? COORD(0, 20) : COORD(0, 32);
	int startBlock = movingDirection == MovingDirection::LEFT ? 19 : -3;

	position = Alignment::GetAlignedPosition(lanePos, startBlock, centerSpot, Gravity::TOP_LEFT);
}
