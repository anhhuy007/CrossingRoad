#include "Lane.h"

void Lane::Update(float elapsedTime) {
}

void Lane::Render() {
	game->RenderSprite(laneSprite, position);
}
