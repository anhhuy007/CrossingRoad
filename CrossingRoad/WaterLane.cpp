#include "WaterLane.h"

void WaterLane::Update(float elapsedTime) {
	log.Update(elapsedTime);

	if (log.endOfRoad == true) {
		log.endOfRoad = false;
		log.setInitPosition();
		log.logSpeed = float((rand() % 3) + 1) * 0.004;	// reset new log speed
	}

	// update collision points
	WriteCollisionPoints();
}

void WaterLane::Render() {
	game->RenderSprite(laneSprite, position);
	game->RenderSprite(log.logSprite, log.getPosition());
}

void WaterLane::ScrollUp() {
	id++;
	position.Y += 24;
	log.MoveDown();
}
