#include "GrassLane.h"

void GrassLane::Render() {
	game->RenderSprite(laneSprite, position);
	for (int i = 0; i < trees.size(); i++) {
		game->RenderSprite(trees[i].treeSprite, trees[i].getPosition());
	}
}

void GrassLane::Update(float elapsedTime) {
	for (auto& tree : trees) {
		tree.WriteCollisionPoints();
	}
}

void GrassLane::ScrollUp() {
	id++;
	position.Y += 24;

	// move trees down
	for (auto& tree : trees) {
		tree.MoveDown();
	}
}
