#include "Coin.h"

Coin::Coin() : GameObject(nullptr) {
	// coin not initialized
	lanePos = -1;
};

Coin::Coin(
	CrossingRoad* game,
	int planePos
) : GameObject(game) {
	// set sprite and position
	lanePos = planePos;
	axisSpeed = GameSpeed(0, 0, -11, 21);
	coinSprite = Graphic::Sprite(DrawableRes::Coin, Overlapped::DECORATOR);

	int blockPos = rand() % 6 + 6;
	position = Alignment::GetAlignedPosition(
		lanePos,
		blockPos,
		{ 9, 7 },
		Gravity::CENTRALLY_ALIGNED
	);

	setCollisionPoints(Factory::GetObjectCollisionPoints(ObjectType::COIN));
}

void Coin::Update(float elapsedTime) {
	if (lanePos != -1 && !isCollected) {
		WriteCollisionPoints();
	}
}

void Coin::Render() {
	if (lanePos != -1 && !isCollected) {
		game->RenderSprite(coinSprite, position);
	}
}

void Coin::MoveDown() {
	if (lanePos == -1) return;

	position.X += axisSpeed.X_VERTICAL;
	position.Y += axisSpeed.Y_VERTICAL;
	if (lanePos % 3 == 0) {
		position.X += 1;
		position.Y += 1;
	}
	lanePos += 1;
}
