#include "Factory.h"

std::vector<AnimationSprite> Factory::GetPlayerSprite(Player player) {
	std::vector<AnimationSprite> ans;
	int numberOfAnimations = 8;

	std::vector<AnimationState> animations = {
		AnimationState::NORMAL,
		AnimationState::TURN_LEFT,
		AnimationState::TURN_RIGHT,
		AnimationState::TURN_BACK,
		AnimationState::JUMP_AHEAD,
		AnimationState::JUMP_LEFT,
		AnimationState::JUMP_RIGHT,
		AnimationState::JUMP_BACK,
	};

	std::vector<std::string> spriteFiles = {
			DrawableRes::animationSprite1,
			DrawableRes::animationSprite2,
			DrawableRes::animationSprite3,
			DrawableRes::animationSprite4,
			DrawableRes::animationSprite5,
			DrawableRes::animationSprite6,
			DrawableRes::animationSprite7,
			DrawableRes::animationSprite8,
	};

	std::string folder = "";

	// get player sprite folder
	switch (player) {
	case Player::CHICK:
		folder = "Chick\\";
		break;
	default:
		break;
	}

	for (int i = 0; i < numberOfAnimations; i++) {
		std::string spritePath = DrawableRes::spriteFolder + folder + spriteFiles[i];
		ans.push_back(
			AnimationSprite(
				Graphic::Sprite(spritePath, Overlapped::PLAYER),
				animations[i]
			)
		);
	}

	return ans;
}
