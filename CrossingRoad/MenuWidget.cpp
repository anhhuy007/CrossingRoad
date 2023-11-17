#include "MenuWidget.h"

MenuWidget::MenuWidget(
	CrossingRoad* pgame,
	vector<Widget::Button> pbuttons,
	COORD pposition
) : GameObject(pgame) {
	position = pposition;
	buttons = pbuttons;
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
		buttons[currentButtonIndex].OnChosen();
	}

	// update button state
	for (int i = 0; i < buttons.size(); i++) {
		if (i == currentButtonIndex) {
			buttons[i].OnChosen();
		}
		else {
			buttons[i].OnNormal();
		}
	}
}
