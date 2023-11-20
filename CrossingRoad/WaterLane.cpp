#include "WaterLane.h"

void WaterLane::Update(float elapsedTime) {
	log.Update(elapsedTime);

	if (log.endOfRoad == true) {
		log.endOfRoad = false;
		log.setInitPosition();
		log.logSpeed = float((rand() % 3) + 1) * 0.004;	// reset new log speed
	}

	if (isScrolling) {
		// move lane down
		position.Y++;
		/*vehicle.MoveAhead();
		vehicle.MoveDown();*/

		if (position.Y >= expectedPosition.Y) {
			position.Y = expectedPosition.Y;
			isScrolling = false;
		}
	}
}

void WaterLane::Render() {
	game->RenderSprite(laneSprite, position);
	game->RenderSprite(log.logSprite, log.getPosition());
}

void WaterLane::ScrollUp() {
	/*id++;
	position.Y += 24;*/
	id++;
	expectedPosition.Y += 24;
	isScrolling = true;

	log.lanePos++;

	int sign = log.movingDirection == MovingDirection::LEFT ? 1 : -1;
	int numMove = log.getPosition().X;
	int blockPos = log.movingDirection == MovingDirection::LEFT ? 17 : 0;
	COORD pos = Alignment::getAlignedPosition(log.lanePos, blockPos, { 3, 15 }, Gravity::LEFT_CENTER);

	numMove = (numMove - pos.X) / log.axisSpeed.X_HORIZONTAL;

	log.setInitPosition();
	pos = log.getPosition();
	log.setPosition({
		short(pos.X + numMove * log.axisSpeed.X_HORIZONTAL * sign),
		short(pos.Y + numMove * log.axisSpeed.Y_HORIZONTAL * sign)
	});
}
