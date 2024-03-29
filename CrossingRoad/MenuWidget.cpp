#include "MenuScreen.h"
#include "SettingScreen.h"
#include "PlayMenuScreen.h"

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
		button.text.SetTextPosition(
			button.text.text,
			Widget::GetMessageImgPos(
				{ short(pos.X + 43), short(pos.Y + 18) },
				90, 20,
				button.text.text.length() * 5, 5
			),
			90, 20
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
	auto checkIndex = [max = (int)buttons.size() - 1, _game = game](int& i) {
		if (i < 0 || i > max) {
			_game->sound->playEffectSound( int(Sound::Effect::INVALID));
			i = max(0, i);
			i = min(max, i);
			return 0;
		}
		_game->sound->playEffectSound(int(Sound::Effect::CHANGE));
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
		game->sound->playEffectSound(int(Sound::Effect::ENTER));
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
		if (totalTime > 200) {
			buttons[currentButtonIndex].action();
			enterClicked = false;
			totalTime = 0;
			// reset button text position
			COORD pos = buttons[currentButtonIndex].getPosition();
			buttons[currentButtonIndex].text.SetTextPosition(
				buttons[currentButtonIndex].text.text,
				Widget::GetCenterTextPos(
					buttons[currentButtonIndex].text.text,
					{ short(pos.X + 43), short(pos.Y + 18) },
					90, 20
				),
				90, 20
			);
		}
	}
}