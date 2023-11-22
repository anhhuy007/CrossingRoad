#include "MenuScreen.h"
#include "StreetMap.h"
#include "SettingScreen.h"
#include "PlayMenuScreen.h"

PlayMenuWidget::PlayMenuWidget(
	CrossingRoad* pgame,
	std::vector<Widget::Button>& pbuttons,
	COORD pposition
) : GameObject(pgame) {
	position = pposition;
	buttons = pbuttons;

	// set button positions
	COORD pos = pposition;
	for (auto& button : buttons) {
		button.setPosition(pos);

		// set button text positions
		button.text.setTextPosition(
			button.text.text,
			Widget::GetCenterTextPos(button.text.text, pos, 140, 34),
			138,
			34
		);

		pos.Y += 30;

	}
}

void PlayMenuWidget::Render() {
	for (int i = 0; i < buttons.size(); i++) {
		buttons[i].Render();
	}
}

void PlayMenuWidget::Update(float elapsedTime) {
	auto checkIndex = [max = (int)buttons.size() - 1, _game = game](int& i) {
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
		checkIndex(--currentButtonIndex);
	}
	else if (game->inputHandle->keyState_[Keyboard::DOWN_KEY].isPressed) {
		checkIndex(++currentButtonIndex);
	}
	else if (game->inputHandle->keyState_[Keyboard::ENTER_KEY].isPressed) {
		enterClicked = true;
		Sound::playEffectSound(game->soundSetting, int(Sound::Effect::ENTER));
	}

	// update button state
	for (int i = 0; i < buttons.size(); i++) {
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
	}

	// trigger button action
	if (enterClicked) {
		totalTime += elapsedTime;
		if (totalTime > 500) {
			buttons[currentButtonIndex].action();

			enterClicked = false;
			totalTime = 0;
			// reset button text position
			buttons[currentButtonIndex].text.setTextPosition(
				buttons[currentButtonIndex].text.text,
				Widget::GetCenterTextPos(buttons[currentButtonIndex].text.text, buttons[currentButtonIndex].getPosition(), 138, 34),
				138,
				34
			);
		}
	}
}