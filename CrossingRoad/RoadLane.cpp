#include "RoadLane.h"

void RoadLane::Update(float elapsedTime) {
	vehicle.Update(elapsedTime);
	if (vehicle.endOfRoad == true) {
		vehicle.endOfRoad = false;
		vehicle.SetInitPosition();
		vehicle.vehicleSpeed = float((rand() % 3) + 1) * 0.004;
	}

	if (isScrolling) {
		// move lane down
		position.Y += 2;
		//vehicle.MoveAhead();
		vehicle.MoveDown();
		

		if (position.Y >= expectedPosition.Y) {
			position.Y = expectedPosition.Y;
			isScrolling = false;
		}
	}
}

void RoadLane::Render() {
	game->RenderSprite(laneSprite, position);
	game->RenderSprite(vehicle.vehicleSprite, vehicle.getPosition());

	// draw road markings
	if (hasRoadMarking) {
		for (int i = 0; i < MAXBLOCK + 5; i+=4) {
			game->RenderSprite(
				roadMarkingSprite,
				Alignment::getAlignedPosition(id, i, { 0, 4 }, Gravity::TOP_LEFT)
			);
		}
	}
}

void RoadLane::ScrollUp() {
	id++;
	expectedPosition.Y += 24;
	isScrolling = true;
	/*id++;
	position.Y += 24;
	vehicle.lanePos++;

	int sign = vehicle.movingDirection == MovingDirection::LEFT ? 1 : -1;
	int numMove = vehicle.getPosition().X;
	int blockPos = vehicle.movingDirection == MovingDirection::LEFT ? 17 : 0;
	COORD pos = Alignment::getAlignedPosition(vehicle.lanePos, blockPos, { 3, 15 }, Gravity::LEFT_CENTER);

	numMove = (numMove - pos.X) / vehicle.axisSpeed.X_HORIZONTAL;

	vehicle.setInitPosition();
	pos = vehicle.getPosition();
	vehicle.setPosition({
		short(pos.X + numMove * vehicle.axisSpeed.X_HORIZONTAL * sign),
		short(pos.Y + numMove * vehicle.axisSpeed.Y_HORIZONTAL * sign)
		});*/
}
