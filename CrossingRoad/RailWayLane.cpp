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
	greenLight = Graphic::Sprite(DrawableRes::GreenLight, Overlapped::TRAFFIC_LIGHT);
	redLight = Graphic::Sprite(DrawableRes::RedLight, Overlapped::TRAFFIC_LIGHT);
	trafficLightPos = id;
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
	greenLight = Graphic::Sprite(DrawableRes::GreenLight, Overlapped::TRAFFIC_LIGHT);
	redLight = Graphic::Sprite(DrawableRes::RedLight, Overlapped::TRAFFIC_LIGHT);
	trafficLightPos = id;
}

void RailWayLane::Update(float elapsedTime)
{
	train.Update(elapsedTime);
	if (train.endOfRoad == true) {
		time += elapsedTime;
		isTrain = false;

		if (time >= trainTime) {
			isTrain = true;
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
	if (isTrain == true) {
		game->RenderSprite(redLight, Alignment::GetAlignedPosition(
			trafficLightPos, 10,
			{ 15, 43 },
			Gravity::BOTTOM_CENTER
		));
		game->sound->playEffectSound(int(Sound::Effect::TRAIN));
	}
	else {
		game->RenderSprite(greenLight, Alignment::GetAlignedPosition(
			trafficLightPos, 10,
			{ 15, 43 },
			Gravity::BOTTOM_CENTER
		));
	}
}

void RailWayLane::ScrollUp()
{
	id++;
	position.Y += 24;
	train.MoveDown(train.lanePos);
	trafficLightPos++;
}

Vehicle RailWayLane::GetVehicle()
{
	return train;
}
