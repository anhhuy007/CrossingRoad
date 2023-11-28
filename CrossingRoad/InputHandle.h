#pragma once

#include <Windows.h>   
#include <WinUser.h>

class InputHandle {
	
	struct KeyState {
		bool isPressed;
		bool isReleased;
		bool isHeld;
	};

protected: 
	InputHandle();

	static InputHandle* inputHandle_;

	short keyOldState_[256];
	short keyNewState_[256];

	KeyState GetKey(int keyId);

public:
	KeyState keyState_[256];		// handle all key states

	InputHandle(InputHandle& other) = delete;
	void operator=(const InputHandle&) = delete;

	static InputHandle* GetKeyBoardState();
};
