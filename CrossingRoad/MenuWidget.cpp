#include "MenuWidget.h"

MenuWidget::MenuWidget(
	CrossingRoad* pgame,
	vector<Widget::Button>& pbuttons,
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
		enterClicked = true;
	}

	// update button state
	if (enterClicked) {
		buttons[currentButtonIndex].OnEnter();
		Render();
		game->UpdateConsole();

		// play sfx
		//game->sound->PlaySfx(Sfx::BUTTON_CLICK);

		// delay 0.5s
		Sleep(500);

		// execute button action
		buttons[currentButtonIndex].action();
	}
	else {
		for (int i = 0; i < buttons.size(); i++) {
			if (i == currentButtonIndex) {
				buttons[i].OnChosen();
			}
			else {
				buttons[i].OnNormal();
			}
		}
	}

	Render();
}
