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
}


Lane::Lane(const Lane& lane) : GameObject(lane) {
	this->id = lane.id;
	this->laneSprite = lane.laneSprite;
	this->game = lane.game;
	this->laneType = lane.laneType;
}

