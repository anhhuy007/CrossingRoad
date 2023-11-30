#include "SnowLane.h"

SnowLane::SnowLane(
	int id,
	CrossingRoad* game,
	Graphic::Sprite _snowSprite,
	int numberOfTree,
	int numberOfRock
) : Lane(id, game, _snowSprite, LaneType::SNOW) {
	// generate random trees, rocks, gifts, deers and snowman
	for (int i = 0; i < 20; i++) {
		int random = rand() % 6;
		if (random == 5 && numberOfRock > 0) {
			objectCoord[i] = rand() % 2 == 0 ? 5 : 6;
			numberOfRock--;
		}
		else if (random == 4 && numberOfTree && objectCoord[max(i - 1, 0)] == 0) {
			objectCoord[i] = rand() % 2 == 0 ? 3 : 4;
			numberOfTree--;
		}
		else if (random == 3 && numberOfTree > 0) {
			objectCoord[i] = rand() % 2 == 0 ? 1 : 2;	// small tree
			numberOfTree--;
		}
		else {
			objectCoord[i] = 0;
		}
	}

	for (int i = 0; i < 20; i++) {
		if (objectCoord[i] == 1) {
			trees.push_back(Tree(game, id, i, ObjectType::SMALL_PINETREE, DrawableRes::PineTree1));
		}
		else if (objectCoord[i] == 2) {
			trees.push_back(Tree(game, id, i, ObjectType::SNOWMAN, DrawableRes::Snowman));
		}
		else if (objectCoord[i] == 3) {
			trees.push_back(Tree(game, id, i, ObjectType::BIG_PINETREE, DrawableRes::PineTree2));
			i++;

			// adjust tree position
			COORD pos = trees[trees.size() - 1].getPosition();
			trees[trees.size() - 1].setPosition({ pos.X, short(pos.Y - 5) });
		}
		else if (objectCoord[i] == 4) {
			trees.push_back(Tree(game, id, i, ObjectType::DEER, DrawableRes::Deer));
			i++;
		}
		else if (objectCoord[i] == 5) {
			rocks.push_back(Rock(game, id, i, ObjectType::SNOW_ROCK, DrawableRes::Rock_Snow));
		}
		else if (objectCoord[i] == 6) {
			rocks.push_back(Rock(game, id, i, ObjectType::GIFT, DrawableRes::Gift));
		}
	}
};

void SnowLane::Render() {
	game->RenderSprite(laneSprite, position);
	for (int i = 0; i < trees.size(); i++) {
		game->RenderSprite(trees[i].treeSprite, trees[i].getPosition());
	}

	for (int i = 0; i < rocks.size(); i++) {
		game->RenderSprite(rocks[i].rockSprite, rocks[i].getPosition());
	}
}

void SnowLane::Update(float elapsedTime) {
	for (auto& tree : trees) {
		tree.WriteCollisionPoints();
	}

	for (auto& rock : rocks) {
		rock.WriteCollisionPoints();
	}
}

void SnowLane::ScrollUp() {
	id++;
	position.Y += 24;

	// move trees down
	for (auto& tree : trees) {
		tree.MoveDown(tree.lanePos);
	}

	// move rocks down
	for (auto& rock : rocks) {
		rock.MoveDown(rock.lanePos);
	}
}
