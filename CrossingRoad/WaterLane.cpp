#include "WaterLane.h"

WaterLane::WaterLane(
	int id, 
	CrossingRoad* game, 
	MovingDirection pdirection,
	Graphic::Sprite waterSprite
) : Lane(id, game, waterSprite, LaneType::WATER) {
	// generate random log
	direction = pdirection;
	log = Log(game, id, direction);
	SetCollisionPoints(Factory::GetObjectCollisionPoints(ObjectType::WATER));
}
WaterLane::WaterLane(
	int id, 
	CrossingRoad* game, 
	Graphic::Sprite waterSprite, 
	LaneInfo laneInfo
) : Lane(id, game, waterSprite, LaneType::WATER) {
	// generate random log
	direction = laneInfo.objectDirection;
	log = Log(game, id, direction, laneInfo.objectsInfo[0]);
	log.logSprite.SetOverlapped(Overlapped::LOG);
	SetCollisionPoints(Factory::GetObjectCollisionPoints(ObjectType::WATER));
}

void WaterLane::Update(float elapsedTime) {
	log.Update(elapsedTime);

	if (log.endOfRoad == true) {
		log.endOfRoad = false;
		log.SetInitPosition();
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
	log.MoveDown(log.lanePos);
}

Log WaterLane::GetLog()
{
	return log;
}
