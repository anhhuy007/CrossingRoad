#include "WaterLane.h"

void WaterLane::Update(float elapsedTime) {
	log.Update(elapsedTime);

	if (log.endOfRoad == true) {
		log.endOfRoad = false;
		//vehicle = Vehicle(game, id, direction);
		log.setInitPosition();
		log.logSpeed = float((rand() % 3) + 1) * 0.004;
	}
}

void WaterLane::Render() {
	game->RenderSprite(laneSprite, position);
	game->RenderSprite(log.logSprite, log.getPosition());
}