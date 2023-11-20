#include "GrassLane.h"

void GrassLane::Render() {
	game->RenderSprite(laneSprite, position);
	for (int i = 0; i < trees.size(); i++) {
		game->RenderSprite(trees[i].treeSprite, trees[i].getPosition());
	}
}

void GrassLane::Update(float elapsedTime) {
	if (isScrolling) {
		// move lane down
		position.Y++;
		/*vehicle.MoveAhead();
		vehicle.MoveDown();*/

		if (position.Y >= expectedPosition.Y) {
			position.Y = expectedPosition.Y;
			isScrolling = false;
		}
	}
}

void GrassLane::ScrollUp() {
	id++;
	expectedPosition.Y += 24;
	isScrolling = true;

	// move trees down
	/*for (auto& tree : trees) {
		tree.lanePos++;

		if (tree.treeType == TreeType::SMALL_TREE) {
			tree.setPosition(
				Alignment::getAlignedPosition(
					tree.lanePos,
					tree.blockPos,
					{ 10, 40 },
					Gravity::CENTRALLY_ALIGNED
				)
			);
		}
		else {
			tree.setPosition(
				Alignment::getAlignedPosition(
					tree.lanePos,
					tree.blockPos,
					{ 26, 63 },
					Gravity::BOTTOM_CENTER
				)
			);
		}
	}*/
}
