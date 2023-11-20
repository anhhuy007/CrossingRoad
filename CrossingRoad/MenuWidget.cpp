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

	// check button index
	currentButtonIndex = max(0, currentButtonIndex);
	currentButtonIndex = min((int)buttons.size() - 1, currentButtonIndex);

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
			enterClicked = false;
			totalTime = 0;
			buttons[currentButtonIndex].action();
		}
	}
}
