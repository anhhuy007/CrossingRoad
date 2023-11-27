#include "Portal.h"

Portal::Portal(CrossingRoad* game) : GameObject(game) {
	portalSprite = Graphic::Sprite(DrawableRes::Portal, Overlapped::DECORATOR);
	setCollisionPoints(Factory::GetObjectCollisionPoints(ObjectType::PORTAL));
}

void Portal::Render() {
	if (visible) {
		game->RenderSprite(portalSprite, position);
	}
}
