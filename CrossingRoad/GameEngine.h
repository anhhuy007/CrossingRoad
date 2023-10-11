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

using namespace std;

// MY CLASS INCLUDES
#include "Colors.h"
#include "TextStrings.h"
#include "Alignment.h"
#include "GameObject.h"

class GameEngine {
private: 
	void SetWindowSize(int width, int height);
	void SetScreenBufferSize(int width, int height);
	
public: 
	// class funtions
	GameEngine();
	~GameEngine();
	
	// ----- Window console funtions -----
	void BuildConsole();
	SMALL_RECT GetWindowSize();

	// ----- Screen buffer funtions -----
	void bindObjectToScreenBuffer(GameObject object);

	// ----- Sound funtions -----

protected:
	int fontSize;
	SMALL_RECT windowScope;
	PCHAR_INFO screenBuffer;    // store screen buffer info to display in each frame
};

#endif // _GAME_ENGINE_H_