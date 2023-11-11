#include "GrassLane.h"

void GrassLane::Render() {
	game->RenderSprite(laneSprite, position);
	for (int i = 0; i < trees.size(); i++) {
		game->RenderSprite(trees[i].treeSprite, trees[i].getPosition());
	}
}