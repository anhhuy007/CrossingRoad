//#pragma once
//
//#include <WinUser.h>
//
//class InputHandle {
//public: 
//	bool keyOldState[256];
//	bool keyNewState[256];
//	
//	struct KeyState {
//		bool isPressed;
//		bool isReleased;
//		bool isHeld;
//	} arrKeyState[256];
//
//	KeyState GetKey(int keyId);
//
//	enum class KEYBOARD {
//		UP = VK_UP,
//		DOWN = VK_DOWN,
//		LEFT = VK_LEFT,
//		RIGHT = VK_RIGHT,
//		SPACE = VK_SPACE,
//		ENTER = VK_RETURN,
//		ESCAPE = VK_ESCAPE,
//	};
//	
//	InputHandle();
//}