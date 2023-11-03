#include "RoadLane.h"

void RoadLane::Update(float elapsedTime) {
	vehicle.Update(elapsedTime);
	if (vehicle.endOfRoad == true) {
		vehicle.endOfRoad = false;
		//vehicle = Vehicle(game, id, direction);
		vehicle.setInitPosition();
	}
}

void RoadLane::Render() {
	game->RenderSprite(laneSprite, position);
	game->RenderSprite(vehicle.vehicleSprite, vehicle.getPosition());
}