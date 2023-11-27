#include "GrassLane.h"

GrassLane::GrassLane(
	int id, 
	CrossingRoad* game, 
	Graphic::Sprite _grassSprite,
	int numberOfTree,
	int numberOfRock
) : Lane(id, game, _grassSprite, LaneType::GRASS) {
	// generate random trees and rocks
	for (int i = 0; i < 20; i++) {
		int random = rand() % 6;
		if (random == 5 && numberOfRock > 0) {
			objectCoord[i] = 3;	// rock
			numberOfRock--;
		}
		else if (random == 4 && numberOfTree && objectCoord[max(i - 1, 0)] == 0) {
			objectCoord[i] = 2;	// big tree
			numberOfTree--;
		}
		else if (random == 3 && numberOfTree > 0) {
			objectCoord[i] = 1;	// small tree
			numberOfTree--;
		}
		else {
			objectCoord[i] = 0;
		}
	}

	for (int i = 0; i < 20; i++) {
		if (objectCoord[i] == 1) {
			trees.push_back(Tree(game, id, i, TreeType::SMALL_TREE, DrawableRes::SmallTree));
		}
		else if (objectCoord[i] == 2) {
			trees.push_back(Tree(game, id, i, TreeType::BIG_TREE, DrawableRes::BigTree));
			i++;
		}
		else if (objectCoord[i] == 3) {
			rocks.push_back(Rock(game, id, i, DrawableRes::Rock));
		}
	}
};

void GrassLane::Render() {
	game->RenderSprite(laneSprite, position);
	for (int i = 0; i < trees.size(); i++) {
		game->RenderSprite(trees[i].treeSprite, trees[i].getPosition());
	}

	for (int i = 0; i < rocks.size(); i++) {
		game->RenderSprite(rocks[i].rockSprite, rocks[i].getPosition());
	}
}

void GrassLane::Update(float elapsedTime) {
	for (auto& tree : trees) {
		tree.WriteCollisionPoints();
	}

	for (auto& rock : rocks) {
		rock.WriteCollisionPoints();
	}
}

void GrassLane::ScrollUp() {
	id++;
	position.Y += 24;

	// move trees down
	for (auto& tree : trees) {
		tree.MoveDown();
	}

	// move rocks down
	for (auto& rock : rocks) {
		rock.MoveDown();
	}
}
