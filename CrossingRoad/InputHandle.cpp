#include "InputHandle.h"

InputHandle* InputHandle::inputHandle_ = nullptr;

InputHandle::InputHandle() {
	for (int i = 0; i < 256; i++) {
		keyOldState_[i] = false;
		keyNewState_[i] = false;
		keyState_[i] = { false, false, false };
	}
}

InputHandle::KeyState InputHandle::GetKey(int keyId) {
	return keyState_[keyId];
}

InputHandle* InputHandle::GetKeyBoardState() {
	if (inputHandle_ == nullptr) {
		inputHandle_ = new InputHandle();
	}

	// ----- Update input state -----
	for (int i = 0; i < 256; i++) {
		inputHandle_->keyNewState_[i] = GetAsyncKeyState(i);

		inputHandle_->keyState_[i].isPressed = false;
		inputHandle_->keyState_[i].isReleased = false;

		if (inputHandle_->keyNewState_[i] != inputHandle_->keyOldState_[i]) {
			if (inputHandle_->keyNewState_[i] & 0x8000) {	// if key is pressed
				inputHandle_->keyState_[i].isPressed = !inputHandle_->keyState_[i].isHeld; // avoid keyboard holding
				//inputHandle_->keyState_[i].isPressed = true; // for keyboard holding
				inputHandle_->keyState_[i].isHeld = true;
			}
			else {
				inputHandle_->keyState_[i].isReleased = true;
				inputHandle_->keyState_[i].isHeld = false;
			}
		}

		inputHandle_->keyOldState_[i] = inputHandle_->keyNewState_[i];
	}

	/*for (int i = 0; i < 256; i++) {
		int temp = GetAsyncKeyState(i) & 0x8000;
		inputHandle_->keyState_[i].isPressed = temp == 1 ? true : false;
	}*/

	return inputHandle_;
}

short InputHandle::GetKeyId(char key)
{
	// return alphabet and number key id
	if (key >= 'A' && key <= 'Z') {
		return key - 'A' + 65;
	}
	else if (key >= '0' && key <= '9') {
		return key - '0' + 48;
	}
	else {
		return -1;
	}
}
