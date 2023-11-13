#include "Animation.h"

Animation::Animation(
	std::vector<Image> pimages,
	int pdelay
) {
	delay = pdelay;
	for (auto& image : pimages) {
		images.push_back(image);
	}
}

void Animation::PlayAnimation(CrossingRoad* game, COORD position) {
	for (const auto& image : images) {
		game->RenderSprite(image, position);								// display image
		std::this_thread::sleep_for(std::chrono::milliseconds(delay));		// delay each frame
	}
}

void Animation::Play(CrossingRoad* game, COORD position) {
	std::thread animationThread(&Animation::PlayAnimation, this, game, position);

	animationThread.join();
}