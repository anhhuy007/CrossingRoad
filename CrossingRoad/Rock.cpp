#include "Rock.h"

Rock::Rock(
	CrossingRoad* game,
	int planePos,
	int pblockPos,
	Graphic::Sprite pSprite
) : GameObject(game)
{
	lanePos = planePos;
	blockPos = pblockPos;
	rockSprite = pSprite;

	position = Alignment::GetAlignedPosition(
		lanePos,
		blockPos,
		{ 11, 16 },
		Gravity::CENTRALLY_ALIGNED
	);
	width = 27;
	height = 24;
	collisionPoints = Factory::GetObjectCollisionPoints(ObjectType::ROCK);
}