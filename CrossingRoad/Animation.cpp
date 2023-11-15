#include "Animation.h"

Animation::Animation(
	CrossingRoad* pgame,
	std::vector<Image> pimages,
	COORD pposition,
	int pdelay
) {
	game = pgame;
	position = pposition;
	delay = pdelay;
	for (auto& image : pimages) {
		images.push_back(image);
	}
}

void Animation::OnPlay(float elapsedTime) {
	if (isPause) return;

	totalTime += elapsedTime;	
	if (totalTime >= delay) {
		totalTime = 0;
		frameId = (frameId + 1) % images.size();
	}

	game->RenderSprite(images[frameId], position);	// display frames

	if (game->inputHandle->keyState_[Keyboard::ESCAPE_KEY].isPressed) {
		isPause = true;
		return;
	}
}

void Animation::OnPause() {
	isPause = true;
}

void Animation::OnResume() {
	isPause = false;
}

