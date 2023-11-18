#include "MenuWidget.h"

MenuWidget::MenuWidget(
	CrossingRoad* pgame,
	vector<Widget::Button>& pbuttons,
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
			Widget::GetCenterTextPos(button.text.text, pos, 120, 34),
			112,
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
		currentButtonIndex--;
	}
	else if (game->inputHandle->keyState_[Keyboard::DOWN_KEY].isPressed) {
		currentButtonIndex++;
	}
	else if (game->inputHandle->keyState_[Keyboard::ENTER_KEY].isPressed) {
		enterClicked = true;
	}

	// update button state
	if (enterClicked) {
		buttons[currentButtonIndex].OnTrigger();
	}
	else {
		for (int i = 0; i < buttons.size(); i++) {
			if (i == currentButtonIndex) {
				buttons[i].OnHover();
			}
			else {
				buttons[i].OnNormal();
			}
		}
	}

	for (int i = 0; i < buttons.size(); i++) {
		buttons[i].Update(elapsedTime);
	}
}
