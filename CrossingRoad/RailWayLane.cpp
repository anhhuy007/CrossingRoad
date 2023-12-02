#include "RailWayLane.h"

RailWayLane::RailWayLane(
	int id,
	CrossingRoad* game,
	Graphic::Sprite railWaySprite
) : Lane(id, game, railWaySprite, LaneType::RAILWAY)
{
	MovingDirection randomDirection = MovingDirection::LEFT;
	train = Vehicle(game, id, randomDirection, ObjectType::TRAIN);
	trainTime = 7000 + float(rand() % 4) * 1000;
}

RailWayLane::RailWayLane(
	int id,
	CrossingRoad* game,
	Graphic::Sprite railWaySprite,
	LaneInfo laneInfo
) : Lane(id, game, railWaySprite, LaneType::RAILWAY)
{
	MovingDirection randomDirection = MovingDirection::LEFT;
	train = Vehicle(game, id, randomDirection, laneInfo.objectsInfo[0]);
	trainTime = 7000 + float(rand() % 4) * 1000;
}

void RailWayLane::Update(float elapsedTime)
{
	train.Update(elapsedTime);
	if (train.endOfRoad == true) {
		time += elapsedTime;

		if (time >= trainTime) {
			train.endOfRoad = false;
			train.SetInitPosition();
			time = 0.0f;
		}
	}
}

void RailWayLane::Render()
{
	game->RenderSprite(laneSprite, position);
	train.Render();
}

void RailWayLane::ScrollUp()
{
	id++;
	position.Y += 24;
	train.MoveDown(train.lanePos);
}

Vehicle RailWayLane::GetVehicle()
{
	return train;
}
