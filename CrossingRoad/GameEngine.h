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
#include <chrono>
#include <thread>

using namespace std;

// MY CLASS INCLUDES
#include "Colors.h"
#include "TextStrings.h"
#include "InputHandle.h"
#include "Graphic.h"
#include "Values.h"


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

	// ----- Gracphic funtions -----
	void UpdateConsole();
	void ClearConsole();
	void RenderSprite(Graphic::Sprite sprite, COORD position);
	
	// ----- Must be overrided functions -----
	virtual bool GameCreate() = 0;
	virtual bool GameUpdate(float elapsedTime) = 0;

	//// ----- Optional funtions -----
	//virtual bool GameDestroy();


	// ----- Properties -----
	InputHandle inputHandle;
	void Start();
private:
	void GameLoop();
	
protected:
	int fontSize;
	SMALL_RECT windowScope;
	CHAR_INFO* screenBuffer ;    // store screen buffer info to display in each frame
	int* collistion;
	
public: 
	static atomic<bool> atomActive;  // true if game is running
	PAIR windowSize = PAIR(0, 0);
 };

#endif // _GAME_ENGINE_H_