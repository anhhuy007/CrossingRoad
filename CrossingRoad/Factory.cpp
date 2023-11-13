#include "Factory.h"

char* Factory::GetSpritePath(char* folder, char* fileName) {
	char* ans;

	ans = new char[sizeof(folder) + sizeof(fileName)];
	strcpy(ans, folder);
	strcat(ans, fileName);

	return ans;
}

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
