#include "Factory.h"

std::vector<AnimationSprite> Factory::GetPlayerSprite(Player player) {
	std::vector<AnimationSprite> ans;
	int numberOfAnimations = 6;

	std::vector<AnimationState> animations = {
		AnimationState::NORMAL,
		AnimationState::TURN_LEFT,
		AnimationState::TURN_RIGHT,
		AnimationState::TURN_BACK,
		AnimationState::DEAD,
		AnimationState::DROWN
	};

	std::vector<std::string> spriteFiles = {
			DrawableRes::animationSprite1,
			DrawableRes::animationSprite2,
			DrawableRes::animationSprite3,
			DrawableRes::animationSprite4,
			DrawableRes::animationSprite5,
			DrawableRes::animationSprite6
	};

	std::string folder = "";

	// get player sprite folder
	switch (player) {

	case Player::CHICK:
		folder = "Chick\\";

		break;

	case Player::DUCKY:
		folder = "Ducky\\";

		break;

	default:
		break;
	}

	for (int i = 0; i < animations.size(); i++) {
		std::string spritePath = DrawableRes::spriteFolder + folder + spriteFiles[i];
		ans.push_back(
			AnimationSprite(
				Graphic::Sprite(spritePath, Overlapped::PLAYER),
				animations[i]
			)
		);
	}

	// drown animation will be overlapped by log
	ans[ans.size() - 1].sprite.SetOverlapped(Overlapped::DECORATOR);

	return ans;
}

std::vector<CollisionPoint> Factory::GetObjectCollisionPoints(ObjectType objType) {
	/*
		COLLISSION VALUES:
		0: no collision
		1: player 
		2: item
		3: tree, rock, bush
		4: car, truck, water 
		5: floating object	
	*/
	std::vector<CollisionPoint> points;

	switch (objType)
	{
	case ObjectType::PLAYER:
		points = GetPointsOnLine(
			{ 12, 14 },
			{ 8, 23 },
			1,
			false
		);

		sum(points, GetPointsOnLine(
			{ 12, 14 },
			{ 23, 16 },
			1,
			true
		));

		sum(points, GetPointsOnLine(
			{ 24, 16 },
			{ 20, 25 },
			1,
			false
		));

		sum(points, GetPointsOnLine(
			{ 8, 23 },
			{ 19, 25 },
			1,
			true
		));

		break;
	case ObjectType::CAR:
		points =  GetPointsOnLine(
			{ 1, 27 },
			{ 72, 44 },
			4,
			true
		);

		break;
	case ObjectType::TRUCK:
		points = GetPointsOnLine(
			{ 1, 40 },
			{ 112, 67 },
			4,
			true
		);

		break;
	case ObjectType::TREE_1:
		points = GetPointsOnLine(
			{ 1, 31 },
			{ 20, 35 },
			3,
			true
		);

		sum(points, GetPointsOnLine(
			{ 1, 42 },
			{ 21, 47 },
			3,
			true
		));

		break;
	case ObjectType::TREE_2:
		points = GetPointsOnLine(
			{ 1, 43 },
			{ 41, 53 },
			3,
			true
		);

		sum(points, GetPointsOnLine(
			{ 1, 51 },
			{ 45, 62 },
			3,
			true
		));

		break;
	case ObjectType::ROCK:
		break;
	case ObjectType::WATER:
		points = GetPointsOnLine(
			{ 1, 13 },
			{ 461, 128 },
			4,
			true
		);

		break;
	case ObjectType::FLOATING_OBJECT_1:
		points = GetPointsOnLine(
			{ 11, 8 },
			{ 94, 28 },
			5,
			true
		);

		break;
	case ObjectType::FLOATING_OBJECT_2:
		points = GetPointsOnLine(
			{ 11, 8 },
			{ 69, 22 },
			5,
			true
		);

		break;
	case ObjectType::ITEM:
		break;
	default:
		break;
	}

	return points;
}

// from left to right
std::vector<CollisionPoint> Factory::GetPointsOnLine(
	COORD start,
	COORD end,
	int collisType,
	bool horizontal
) {
	std::vector<CollisionPoint> points;
	COORD pos = start;
	points.push_back({ pos, collisType });

	// horizontal line: left to right
	if (horizontal) {
		while (pos.X != end.X || pos.Y != end.Y) {
			pos.X++;
			// each for horizontal pixels, go down 1 pixel
			if ((pos.X - start.X) % 4 == 0) {
				pos.Y++;
			}

			points.push_back({ pos, collisType });
		}
	}
	// vertical line: top to bottom
	else {
		while (pos.X != end.X || pos.Y != end.Y) {
			pos.Y++;
			// each for horizontal pixels, go down 1 pixel
			if ((pos.Y - start.Y) % 2 == 0) {
				pos.X--;
			}

			points.push_back({ pos, collisType });
		}
	}

	return points;
}

void Factory::sum(
	std::vector<CollisionPoint>& a, 
	std::vector<CollisionPoint> b
) {
	for (auto point : b) {
		a.push_back(point);
	}
}

