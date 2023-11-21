#include "Portal.h"

Portal::Portal(CrossingRoad* game) : GameObject(game) {
	portalSprite = Graphic::Sprite(DrawableRes::Portal, Overlapped::DECORATOR);
	axisSpeed = GameSpeed(4, 1, -11, 21);
	setCollisionPoints(Factory::GetObjectCollisionPoints(ObjectType::PORTAL));
}

void Portal::MoveDown() {
	if (visible) {
		position.X += axisSpeed.X_VERTICAL;
		position.Y += axisSpeed.Y_VERTICAL;
		if (lanePos % 3 == 0) {
			position.X += 1;
			position.Y += 1;
		}
		lanePos += 1;
	}
}

void Portal::Render() {
	if (visible) {
		game->RenderSprite(portalSprite, position);
	}
}
