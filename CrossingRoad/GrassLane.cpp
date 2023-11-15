#include "GrassLane.h"

void GrassLane::Render() {
	game->RenderSprite(laneSprite, position);
	for (int i = 0; i < trees.size(); i++) {
		game->RenderSprite(trees[i].treeSprite, trees[i].getPosition());
	}
}

void GrassLane::ScrollUp() {
	id++;
	// move lane down
	position.Y += 24;

	// move trees down
	for (auto& tree : trees) {
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
	}
}
