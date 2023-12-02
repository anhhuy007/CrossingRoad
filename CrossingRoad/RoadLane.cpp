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

RoadLane::RoadLane(
	int id, 
	CrossingRoad* game, 
	Graphic::Sprite roadSprite, 
	LaneInfo laneInfo
) : Lane(id, game, roadSprite, LaneType::ROAD) {
	direction = laneInfo.objectDirection;
	vehicle = Vehicle(game, id, direction, laneInfo.objectsInfo[0]);
}


void RoadLane::Update(float elapsedTime) {
	vehicle.Update(elapsedTime);
	coin.Update(elapsedTime);
	if (vehicle.endOfRoad == true) {
		vehicle.endOfRoad = false;
		vehicle.SetInitPosition();
		vehicle.vehicleSpeed = 0.001 + float(rand() % 4 + 1) * 0.001;
	}
}

void RoadLane::Render() {
	game->RenderSprite(laneSprite, position);
	vehicle.Render();
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
	vehicle.MoveDown(vehicle.lanePos);
	coin.MoveDown(coin.lanePos);
}

Vehicle RoadLane::GetVehicle()
{
	return vehicle;
}
