#include "Lane.h"

Lane::Lane(
	int id, 
	CrossingRoad* game, 
	Graphic::Sprite laneSprite, 
	LaneType laneType
) : GameObject(460, 138, { 0, short(id * 24 - 144) }, game) {
	this->id = id;
	this->laneSprite = laneSprite;
	this->game = game;
	this->laneType = laneType;

	// Set object type
	if (laneType == LaneType::ROAD) objType = ObjectType::ROAD_LANE;
	else if (laneType == LaneType::WATER) objType = ObjectType::WATER_LANE;
	else if (laneType == LaneType::SNOW) objType = ObjectType::SNOW_LANE;
	else if (laneType == LaneType::RAILWAY) objType = ObjectType::RAILWAY_LANE;
	else objType = ObjectType::GRASS_LANE;
}

Lane::Lane(const Lane& lane) : GameObject(lane) {
	this->id = lane.id;
	this->laneSprite = lane.laneSprite;
	this->game = lane.game;
	this->laneType = lane.laneType;
}

