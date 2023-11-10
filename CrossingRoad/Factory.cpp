#include "Factory.h"

const char* Factory::GetSpritePath(const char* spriteFolder) {
	return "";
}

std::vector<AnimationSprite> Factory::GetAnimationSprites(Player player) {
	std::vector<AnimationSprite> ans;
	int numberOfAnimations = 5;

	std::vector<AnimationState> animations = {
		AnimationState::NORMAL,
		AnimationState::TURN_LEFT,
		AnimationState::TURN_RIGHT,
		AnimationState::TURN_BACK,
		AnimationState::JUMP_AHEAD
	};

	std::vector<const char*> spriteFiles = {
			"Animation1",
			"Animation2",
			"Animation3",
			"Animation4",
			"Animation5"
	};

	switch (player) {
	case Player::CHICKCHUK:
		for (int i = 0; i < numberOfAnimations; i++) {
			const char* spritePath = GetSpritePath("Chick");

			ans.push_back(
				AnimationSprite(
					Graphic::Sprite(spritePath),
					animations[i]
				)
			);
		}

	}


	return ans;
}
