#include "RoadLane.h"

void RoadLane::Update(float elapsedTime) {
	vehicle.Update(elapsedTime);
	if (vehicle.endOfRoad == true) {
		vehicle.endOfRoad = false;
		//vehicle = Vehicle(game, id, direction);
		vehicle.setInitPosition();
		vehicle.vehicleSpeed = float((rand() % 3) + 1) * 0.004;
	}
}

void RoadLane::Render() {
	game->RenderSprite(laneSprite, position);
	game->RenderSprite(vehicle.vehicleSprite, vehicle.getPosition());
	if (hasRoadMarking) {
		for (int i = 0; i < MAXBLOCK + 5; i+=4) {
			game->RenderSprite(
				roadMarkingSprite,
				Alignment::getAlignedPosition(id, i, { 0, 4 }, Gravity::TOP_LEFT)
			);
		}
	}
}