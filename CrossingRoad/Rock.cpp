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

void Rock::MoveDown() {
	position.X += axisSpeed.X_VERTICAL;
	position.Y += axisSpeed.Y_VERTICAL;
	if (lanePos % 3 == 0) {
		position.X += 1;
		position.Y += 1;
	}
	lanePos += 1;
}
