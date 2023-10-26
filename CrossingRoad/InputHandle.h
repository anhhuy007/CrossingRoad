#pragma once

#ifndef INPUT_HANDLE
#define INPUT_HANDLE

class InputHandle {
public:
	bool keyOldState[256];
	bool keyNewState[256];

	struct KeyState {
		bool isPressed;
		bool isReleased;
		bool isHeld;
	} arrKeyState[256];

	KeyState GetKey(int keyId);

	InputHandle();
};


#endif // !INPUT_HANDLE
