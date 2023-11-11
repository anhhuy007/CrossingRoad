#include "Factory.h"

char* Factory::GetSpritePath(char* folder, char* fileName) {
	char* ans;

	ans = new char[sizeof(folder) + sizeof(fileName)];
	strcpy(ans, folder);
	strcat(ans, fileName);

	return ans;
}

std::vector<AnimationSprite> Factory::GetAnimationSprite(Player player) {
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
			StringRes::animationSprite1,
			StringRes::animationSprite2,
			StringRes::animationSprite3,
			StringRes::animationSprite4,
			StringRes::animationSprite5,
			StringRes::animationSprite6,
			StringRes::animationSprite7,
			StringRes::animationSprite8,
	};

	switch (player) {
	case Player::CHICK:
		for (int i = 0; i < numberOfAnimations; i++) {
			const char* folder = "Chick\\";
			char* spritePath = GetSpritePath(const_cast<char*>(folder), spriteFiles[i].data());

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
