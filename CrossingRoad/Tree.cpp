#include "Tree.h"

Tree::Tree(
	CrossingRoad* game,
	int planePos,
	int pblockPos,
	TreeType ptreeType
) : GameObject(game) {

	lanePos = planePos;
	blockPos = pblockPos;

	if (blockPos % 2) {
		treeSprite = Graphic::Sprite(DrawableRes::SmallTree);
		position = Alignment::GetAlignedPosition(
			lanePos,
			blockPos,
			{ 10, 40 },
			Gravity::CENTRALLY_ALIGNED
		);
		treeType = TreeType::SMALL_TREE;
		width = 25;
		height = 42;
		collisionPoints = Factory::GetObjectCollisionPoints(ObjectType::TREE_1);
	}
	else {
		treeSprite = Graphic::Sprite(DrawableRes::BigTree);
		position = Alignment::GetAlignedPosition(
			lanePos,
			blockPos,
			{ 26, 63 },
			Gravity::BOTTOM_CENTER
		);
		treeType = TreeType::BIG_TREE;
		width = 45;
		height = 57;
		collisionPoints = Factory::GetObjectCollisionPoints(ObjectType::TREE_2);
	}

	treeSprite.SetOverlapped(Overlapped::OBSTACLE);
}

void Tree::MoveDown() {
	position.X += axisSpeed.X_VERTICAL;
	position.Y += axisSpeed.Y_VERTICAL;
	if (lanePos % 3 == 0) {
		position.X += 1;
		position.Y += 1;
	}
	lanePos += 1;
}

