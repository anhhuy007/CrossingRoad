#pragma once
#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

/*

This class include all the functions that are used in the game, such as: manage Graphic - screen buffer, Sound funtions, etc.

*/

#ifndef UNICODE
#endif

#ifndef GAME_ENGINE_H		// prevent multiple definitions if this
#define GAME_ENGINE_H		// ..file is included in more than one place


// STANDARD INCLUDES
#include <Windows.h>
#include <iostream>
#include <string>
#include <WinUser.h>
#include <format>
#include <vector>

using namespace std;

// MY CLASS INCLUDES
#include "Colors.h"
#include "TextStrings.h"
#include "Alignment.h"
#include "GameObject.h"
//#include "InputHandle.h"

struct PAIR{
	WORD x;
	WORD y;

	PAIR(const WORD& _x, const WORD& _y) : x(_x), y(_y) {}

	PAIR(const int &_x, const int &_y) {
		this->x = (WORD)_x;
		this->y = (WORD)_y;
	}
};

class GameEngine {
public: 
	// class funtions
	GameEngine();
	~GameEngine();
	
	// ----- Window console funtions -----
	void BuildConsole();

	// ----- Gracphic manager funtions -----
	void bindObjectToScreenBuffer(GameObject object);
	void updateConsole();
	
	// ----- Must be overrided functions -----
	//virtual bool OnGameStart() = 0;
	//virtual bool OnGameUpdate(float elapsedTime) = 0;

	//// ----- Optional funtions -----
	//virtual bool OnGameDestroy();

protected:
	int fontSize;
	SMALL_RECT windowScope;
	PAIR windowSize = PAIR(0, 0);
	CHAR_INFO* screenBuffer ;    // store screen buffer info to display in each frame
	//InputHandle inputHandle;
	
public: 
	static atomic<bool> isRunning;
 };

#endif // _GAME_ENGINE_H_