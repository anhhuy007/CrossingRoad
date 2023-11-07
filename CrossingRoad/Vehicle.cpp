#include "Vehicle.h"

Vehicle::Vehicle(
	CrossingRoad* game, 
	int _id, 
	MovingDirection _direction
) : GameObject(game) {
	int random = rand() % 10;

	if (random % 2) {
		type = VehicleType::CAR;
		vehicleSprite = Graphic::Sprite("Car.sprite");
	}
	else {
		type = VehicleType::TRUCK;
		vehicleSprite = Graphic::Sprite("Truck.sprite");
	}

	setInitPosition();
	id = _id;
	movingDirection = _direction;
	axisSpeed = GameSpeed(4, 1, 0, 0);
	vehicleSpeed = float((rand() % 3) + 1) * 0.004;
	width = vehicleSprite.getWidth();
	height = vehicleSprite.getHeight();
	vehicleSprite.setOverlapped(Overlapped::VEHICLE);
}

void Vehicle::Update(float elapsedTime) {
	time += (elapsedTime / 100000000);

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
	overlapped = Overlapped::VEHICLE;
}

void Vehicle::setInitPosition() {
	if (type == VehicleType::CAR) {
		position.X =  movingDirection == MovingDirection::LEFT ? 460 : 0;
		position.Y = movingDirection == MovingDirection::LEFT ? id * 24 - 44 : id * 24 - 158;
	}
	else if (type == VehicleType::TRUCK) {
		position.X = movingDirection == MovingDirection::LEFT ? 460 : 0;
		position.Y = movingDirection == MovingDirection::LEFT ? id * 24 - 56 : id * 24 - 170;
	}
}
