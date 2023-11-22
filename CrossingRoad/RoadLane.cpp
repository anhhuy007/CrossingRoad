#include "RoadLane.h"

RoadLane::RoadLane(
	int id,
	CrossingRoad* game,
	Graphic::Sprite roadSprite,
	Graphic::Sprite _roadMarkingSprite,
	bool _hasRoadMarking
) : Lane(id, game, roadSprite, LaneType::ROAD) {
	// generate random vehicle
	direction = (rand() % 2) == 0 ? MovingDirection::LEFT : MovingDirection::RIGHT;
	vehicle = Vehicle(game, id, direction);
	hasRoadMarking = _hasRoadMarking;
	roadMarkingSprite = _roadMarkingSprite;

	// create random coin
	if (rand() % 3 == 0) {
		coin = Coin(game, id);
	}
}

void RoadLane::Update(float elapsedTime) {
	vehicle.Update(elapsedTime);
	coin.Update(elapsedTime);
	if (vehicle.endOfRoad == true) {
		vehicle.endOfRoad = false;
		vehicle.SetInitPosition();
		vehicle.vehicleSpeed = 0.001 + (rand() % 4 + 1) * 0.001;
	}

	//if (position.Y < expectedPosition.Y) {
	//	position.Y += 2;

	//	// move vehicle down
	//	vehicle.MoveDown();
	//}
}

void RoadLane::Render() {
	game->RenderSprite(laneSprite, position);
	game->RenderSprite(vehicle.vehicleSprite, vehicle.getPosition());
	coin.Render();

	// draw road markings
	if (hasRoadMarking) {
		for (int i = 0; i < MAXBLOCK + 5; i+=4) {
			game->RenderSprite(
				roadMarkingSprite,
				Alignment::GetAlignedPosition(id, i, { 0, 4 }, Gravity::TOP_LEFT)
			);
		}
	}
}

void RoadLane::ScrollUp() {
	id++;
	position.Y += 24;
	expectedPosition.Y += 24;
	vehicle.MoveDown();
	coin.MoveDown();
}
