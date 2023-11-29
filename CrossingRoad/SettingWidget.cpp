#include "SettingWidget.h"

COORD SettingWidget::getCursorPosition(int currentButtonIndex) {
	if (currentButtonIndex == 0) {
		return musicPosition;
	}
	else if (currentButtonIndex == 1) {
		return sfxPosition;
	}
	else if (currentButtonIndex == 2) {
		return characterPosition;
	}
	else if (currentButtonIndex == 3) {
		return backPosition;
	}
}

Graphic::Sprite SettingWidget::getSpriteVolumeLevel(int volume, bool isOn) {
	if (volume == 0 || isOn == 0) {
		return Graphic::Sprite("Screen\\settingScreen\\lvl0.sprite", Overlapped::DECORATOR);
	}
	else if (volume == 20) {
		return Graphic::Sprite("Screen\\settingScreen\\lvl1.sprite", Overlapped::DECORATOR);
	}
	else if (volume == 40) {
		return Graphic::Sprite("Screen\\settingScreen\\lvl2.sprite", Overlapped::DECORATOR);
	}
	else if (volume == 60) {
		return Graphic::Sprite("Screen\\settingScreen\\lvl3.sprite", Overlapped::DECORATOR);
	}
	else if (volume == 80) {
		return Graphic::Sprite("Screen\\settingScreen\\lvl4.sprite", Overlapped::DECORATOR);
	}
	else if (volume == 100) {
		return Graphic::Sprite("Screen\\settingScreen\\lvl5.sprite", Overlapped::DECORATOR);
	}
	else {
		return Graphic::Sprite("Screen\\settingScreen\\lvl0.sprite", Overlapped::DECORATOR);
	}
}

SettingWidget::SettingWidget(
	CrossingRoad* pgame,
	std::vector<Widget::Button>& pbuttons,
	COORD pposition
) : GameObject(pgame) {
	position = pposition;
	buttons = pbuttons;
}

void SettingWidget::Render() {
	for (int i = 0; i < buttons.size(); i++) {
		buttons[i].Render();
	}
}

void SettingWidget::Update(float elapsedTime) {
	music.Render();
	sfx.Render();
	character.Render();
	back.Render();

	COORD background = { 185, 73 };
	COORD effect = { 185, 104 };

	auto checkSound = [max = (int)buttons.size() - 1, _game = game](int& i) {
		if (i < 0 || i > max) {
			_game->sound->playEffectSound(int(Sound::Effect::INVALID));
			i = max(0, i);
			i = min(max, i);
			return 0;
		}
		_game->sound->playEffectSound( int(Sound::Effect::CHANGE));
		return 1;
		};
	// get key pressed events
	if (game->inputHandle->keyState_[Keyboard::UP_KEY].isPressed) {
		checkSound(--currentButtonIndex);
	}
	else if (game->inputHandle->keyState_[Keyboard::DOWN_KEY].isPressed) {
		checkSound(++currentButtonIndex);
	}
	else if (game->inputHandle->keyState_[Keyboard::ENTER_KEY].isPressed) {
		enterClicked = true;
		game->sound->playEffectSound( int(Sound::Effect::VALID));
		if (currentButtonIndex == 0) {

			if (game->sound->isBackgroundSoundOn()) {
				game->sound->turnOffBackgroundSound();
			}
			else {
				game->sound->turnOnBackgroundSound();
			}
		}
		else if (currentButtonIndex == 1) {
			if (game->sound->isEffectSoundOn()) {
				game->sound->turnOffEffectSound();
			}
			else {
				game->sound->turnOnEffectSound();
			}
		}
	}
	else if (game->inputHandle->keyState_[Keyboard::LEFT_KEY].isPressed) {
		if (currentButtonIndex == 0) {
			if (game->sound->isBackgroundSoundOn()) {
				if (game->sound->turnDownBackgroundVolume()) {
					game->sound->playEffectSound( int(Sound::Effect::VALID));
					if (game->sound->getBackgroundVolume() == 0) {
						game->sound->turnOffBackgroundSound();
					}
				}
				else {
					game->sound->playEffectSound(int(Sound::Effect::INVALID));
				}
			}
			else {
				if (game->sound->getBackgroundVolume() == 0) {
					game->sound->playEffectSound( int(Sound::Effect::INVALID));
				}
				else {
					game->sound->turnDownBackgroundVolume();
					if (game->sound->getBackgroundVolume() != 0) {
						game->sound->turnOnBackgroundSound();
						game->sound->playEffectSound(int(Sound::Effect::VALID));
					}
				}
			}
		}
		else if (currentButtonIndex == 1) {
			if (game->sound->isEffectSoundOn()) {
				if (game->sound->turnDownEffectVolume()) {
					game->sound->playEffectSound(int(Sound::Effect::VALID));
					if (game->sound->getEffectVolume() == 0) {
						game->sound->turnOffEffectSound();
					}
				}
			}
			else {
				game->sound->turnDownEffectVolume();
				if (game->sound->getEffectVolume() != 0) {
					game->sound->turnOnEffectSound();
					game->sound->playEffectSound( int(Sound::Effect::VALID));
				}
			}
		}
	}
	else if (game->inputHandle->keyState_[Keyboard::RIGHT_KEY].isPressed) {
		if (currentButtonIndex == 0) {
			if (game->sound->isBackgroundSoundOn() == 0) {
				game->sound->turnOnBackgroundSound();
			}
			if (game->sound->turnUpBackgroundVolume()) {
				game->sound->playEffectSound( int(Sound::Effect::VALID));
			}
			else {
				game->sound->playEffectSound(int(Sound::Effect::INVALID));
			}
		}
		else if (currentButtonIndex == 1) {
			if (game->sound->isEffectSoundOn() == 0) {
				game->sound->turnOnEffectSound();
			}
			if (game->sound->turnUpEffectVolume()) {
				game->sound->playEffectSound( int(Sound::Effect::VALID));
			}
			else {
				game->sound->playEffectSound( int(Sound::Effect::INVALID));
			}
		}
	}
	game->RenderSprite(cursor, getCursorPosition(currentButtonIndex));

	game->RenderSprite(getSpriteVolumeLevel(game->sound->getBackgroundVolume(),game->sound->isBackgroundSoundOn()), background);
	game->RenderSprite(getSpriteVolumeLevel(game->sound->getEffectVolume(),game->sound->isEffectSoundOn()), effect);

	if (enterClicked) {
		totalTime += elapsedTime;
		if (totalTime > 500) {
			buttons[currentButtonIndex].action();
			enterClicked = false;
			totalTime = 0;
		}
	}
}
