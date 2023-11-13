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

void Animation::PlayAnimation() {
	game->RenderSprite(images[frameId], position);								// display image
	//game->UpdateConsole();

	if (game->inputHandle->keyState_[Keyboard::ESCAPE_KEY].isPressed) {
		isPause = true;
		return;
	}
}

void Animation::OnPlay() {
	if (isPause) return;

	std::thread animationThread(&Animation::PlayAnimation, this);
	animationThread.join();
	frameId = (frameId + 1) % images.size();
}

void Animation::OnPause() {
	isPause = true;
}

void Animation::OnResume() {
	isPause = false;
}

