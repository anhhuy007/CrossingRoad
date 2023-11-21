#include "MenuWidget.h"

MenuWidget::MenuWidget(
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
			Widget::GetCenterTextPos(button.text.text, pos, 138, 34),
			130,
			34
		);

		pos.Y += 30;

	}
}

void MenuWidget::Render() {
	for (int i = 0; i < buttons.size(); i++) {
		buttons[i].Render();
	}
}	

void MenuWidget::Update(float elapsedTime) {
	// get key pressed events
	if (game->inputHandle->keyState_[Keyboard::UP_KEY].isPressed) {
		Sound::playEffectSound(game->soundSetting, int(Sound::Effect::CHANGE));
		currentButtonIndex--;
	}
	else if (game->inputHandle->keyState_[Keyboard::DOWN_KEY].isPressed) {
		Sound::playEffectSound(game->soundSetting, int(Sound::Effect::CHANGE));
		currentButtonIndex++;
	}
	else if (game->inputHandle->keyState_[Keyboard::ENTER_KEY].isPressed) {
		enterClicked = true;
		Sound::playEffectSound(game->soundSetting, int(Sound::Effect::ENTER));
	}

	// check button index
	if (currentButtonIndex < 0 || currentButtonIndex >(int)buttons.size() - 1) {
		Sound::playEffectSound(game->soundSetting, int(Sound::Effect::INVALID));
		currentButtonIndex = max(0, currentButtonIndex);
		currentButtonIndex = min((int)buttons.size() - 1, currentButtonIndex);
	}

	// update button state
	for (int i = 0; i < buttons.size(); i++) {
		if (i == currentButtonIndex) {
			if (enterClicked) {
				buttons[i].OnTrigger();

				// reset button state

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
				130,
				34
			);
		}
	}
}
