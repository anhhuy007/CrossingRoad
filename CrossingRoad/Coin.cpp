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

