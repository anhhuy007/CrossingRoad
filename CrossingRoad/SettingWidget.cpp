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
			Sound::playEffectSound(_game->soundSetting, int(Sound::Effect::INVALID));
			i = max(0, i);
			i = min(max, i);
			return 0;
		}
		Sound::playEffectSound(_game->soundSetting, int(Sound::Effect::CHANGE));
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
		Sound::playEffectSound(game->soundSetting, int(Sound::Effect::VALID));
		if (currentButtonIndex == 0) {
			if (game->soundSetting.backgroundSound) {
				Sound::turnOffBackgroundSound(game->soundSetting, game->soundSetting.currentIndexBackgroundSound);
			}
			else {
				Sound::turnOnBackgroundSound(game->soundSetting, game->soundSetting.currentIndexBackgroundSound);
			}
		}
		else if (currentButtonIndex == 1) {
			if (game->soundSetting.effectSound) {
				Sound::turnOffEffectSound(game->soundSetting);
			}
			else {
				Sound::turnOnEffectSound(game->soundSetting);
			}
		}
	}
	else if (game->inputHandle->keyState_[Keyboard::LEFT_KEY].isPressed) {
		if (currentButtonIndex == 0) {
			if (game->soundSetting.backgroundSound) {
				if (Sound::turnDownBackgroundVolume(game->soundSetting)) {
					Sound::playEffectSound(game->soundSetting, int(Sound::Effect::VALID));
					if (game->soundSetting.backgroundVolume == 0) {
						Sound::turnOffBackgroundSound(game->soundSetting, game->soundSetting.currentIndexBackgroundSound);
					}
				}
				else {
					Sound::playEffectSound(game->soundSetting, int(Sound::Effect::INVALID));
				}
			}
			else {
				if (game->soundSetting.backgroundVolume == 0) {
					Sound::playEffectSound(game->soundSetting, int(Sound::Effect::INVALID));
				}
				else {
					Sound::turnDownBackgroundVolume(game->soundSetting);
					if (game->soundSetting.backgroundVolume != 0) {
						Sound::turnOnBackgroundSound(game->soundSetting, game->soundSetting.currentIndexBackgroundSound);
						Sound::playEffectSound(game->soundSetting, int(Sound::Effect::VALID));
					}
				}
			}
		}
		else if (currentButtonIndex == 1) {
			if (game->soundSetting.effectSound) {
				if (Sound::turnDownEffectVolume(game->soundSetting)) {
					Sound::playEffectSound(game->soundSetting, int(Sound::Effect::VALID));
					if (game->soundSetting.effectVolume == 0) {
						Sound::turnOffEffectSound(game->soundSetting);
					}
				}
			}
			else {
				Sound::turnDownEffectVolume(game->soundSetting);
				if (game->soundSetting.effectVolume != 0) {
					Sound::turnOnEffectSound(game->soundSetting);
					Sound::playEffectSound(game->soundSetting, int(Sound::Effect::VALID));
				}
			}
		}
	}
	else if (game->inputHandle->keyState_[Keyboard::RIGHT_KEY].isPressed) {
		if (currentButtonIndex == 0) {
			if (game->soundSetting.backgroundSound == 0) {
				Sound::turnOnBackgroundSound(game->soundSetting, game->soundSetting.currentIndexBackgroundSound);
			}
			if (Sound::turnUpBackgroundVolume(game->soundSetting)) {
				Sound::playEffectSound(game->soundSetting, int(Sound::Effect::VALID));
			}
			else {
				Sound::playEffectSound(game->soundSetting, int(Sound::Effect::INVALID));
			}
		}
		else if (currentButtonIndex == 1) {
			if (game->soundSetting.effectSound == 0) {
				Sound::turnOnEffectSound(game->soundSetting);
			}
			if (Sound::turnUpEffectVolume(game->soundSetting)) {
				Sound::playEffectSound(game->soundSetting, int(Sound::Effect::VALID));
			}
			else {
				Sound::playEffectSound(game->soundSetting, int(Sound::Effect::INVALID));
			}
		}
	}
	game->RenderSprite(cursor, getCursorPosition(currentButtonIndex));

	game->RenderSprite(getSpriteVolumeLevel(game->soundSetting.backgroundVolume,game->soundSetting.backgroundSound), background);
	game->RenderSprite(getSpriteVolumeLevel(game->soundSetting.effectVolume,game->soundSetting.effectSound), effect);

	// update button state
	/*for (int i = 0; i < buttons.size(); i++) {
		if (i == currentButtonIndex) {
			if (enterClicked) {
				buttons[i].OnTrigger();
			}
			else {
				buttons[i].OnHover();
			}
		}
		else {
			buttons[i].OnNormal();
		}
	}
	for (int i = 0; i < buttons.size(); i++) {
		buttons[i].Render();
	}*/
	
	// trigger button action
	if (enterClicked) {
		
		totalTime += elapsedTime;
		if (totalTime > 500) {
			buttons[currentButtonIndex].action();
			enterClicked = false;
			totalTime = 0;
			//// reset button text position
			//buttons[currentButtonIndex].text.setTextPosition(
			//	buttons[currentButtonIndex].text.text,
			//	Widget::GetCenterTextPos(buttons[currentButtonIndex].text.text, buttons[currentButtonIndex].getPosition(), 140, 34),
			//	138,
			//	34
			//);
		}
	}
}

