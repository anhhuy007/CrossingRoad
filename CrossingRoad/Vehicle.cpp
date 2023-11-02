#include "Vehicle.h"

void Vehicle::Update(float elapsedTime) {
	if (movingDirection == MovingDirection::LEFT) {
		position.X -= axisSpeed.X_HORIZONTAL;
		position.Y -= axisSpeed.Y_HORIZONTAL;
		
		if (position.X < 0) {
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
}

void Vehicle::Render() {
	game->RenderSprite(sprite, position);
}