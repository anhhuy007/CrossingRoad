#include "Tree.h"

Tree::Tree(
	CrossingRoad* game,
	int planePos,
	int pblockPos,
	ObjectType pobjType,
	Graphic::Sprite psprite
) : GameObject(game, pobjType) {

	lanePos = planePos;
	blockPos = pblockPos;
	treeSprite = psprite;

	if (pobjType == ObjectType::SMALL_TREE || 
		pobjType == ObjectType::SMALL_PINETREE || 
		objType == ObjectType::SNOWMAN
	) {
		position = Alignment::GetAlignedPosition(
			lanePos,
			blockPos,
			{ 10, 40 },
			Gravity::CENTRALLY_ALIGNED
		);
		width = 25;
		height = 42;
		collisionPoints = Factory::GetObjectCollisionPoints(ObjectType::SMALL_TREE);
	}
	else {
		position = Alignment::GetAlignedPosition(
			lanePos,
			blockPos,
			{ 26, 63 },
			Gravity::BOTTOM_CENTER
		);
		width = 45;
		height = 57;
		collisionPoints = Factory::GetObjectCollisionPoints(ObjectType::BIG_TREE);
	}

	treeSprite.SetOverlapped(Overlapped::OBSTACLE);
}

