#include "GrassLane.h"

GrassLane::GrassLane(
	int id, 
	CrossingRoad* game, 
	Graphic::Sprite _grassSprite,
	int numberOfTree
) : Lane(id, game, _grassSprite, LaneType::GRASS) {
	// generate random tree

	for (int i = 2; i < numberOfTree; i++) {
		trees.push_back(Tree(game, id));
	}
};

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
