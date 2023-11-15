#include "Vehicle.h"

Vehicle::Vehicle(
	CrossingRoad* game, 
	int _id, 
	MovingDirection _direction
) : GameObject(game) {
	int random = rand() % 2;

	if (random == 0) {
		type = VehicleType::CAR;
		vehicleSprite = _direction == MovingDirection::LEFT
			? Graphic::Sprite(DrawableRes::RaceCarLeft)
			: Graphic::Sprite(DrawableRes::RaceCarRight);
	}
	else {
		type = VehicleType::TRUCK;
		vehicleSprite = _direction == MovingDirection::LEFT
			? Graphic::Sprite(DrawableRes::TruckLeft)
			: Graphic::Sprite(DrawableRes::TruckRight);
	}

	setInitPosition();
	id = _id;
	movingDirection = _direction;
	axisSpeed = GameSpeed(4, 1, 0, 0);
	vehicleSpeed = float((rand() % 3) + 1) * 0.004;
	width = vehicleSprite.getWidth();
	height = vehicleSprite.getHeight();
	vehicleSprite.setOverlapped(Overlapped::OBSTACLE);
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
}

void Vehicle::Render() {};

void Vehicle::setSprite(Graphic::Sprite _sprite) {
	// delete old sprite
	width = _sprite.getWidth();
	height = _sprite.getHeight();
	vehicleSprite = _sprite;
}

void Vehicle::setInitPosition() {
	COORD centerSpot = type == VehicleType::CAR ? COORD(0, 20) : COORD(0, 32);
	int startBlock = movingDirection == MovingDirection::LEFT ? 19 : -3;

	position = Alignment::getAlignedPosition(id, startBlock, centerSpot, Gravity::TOP_LEFT);
}
