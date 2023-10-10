#pragma once

/*

This class include all the functions that are used in the game, such as: Graphic, Sound funtions, etc.

*/

#ifndef UNICODE
#endif

#ifndef GAME_ENGINE_H		// prevent multiple definitions if this
#define GAME_ENGINE_H		// ..file is included in more than one place


// STANDARD INCLUDES
#include <windows.h>
#include <iostream>
#include <string>

using namespace std;

// MY CLASS INCLUDES
#include "Colors.h"
#include "TextString.h"

class GameEngine {
private: 
	static void setWindowSize(int width, int height);
	static void setScreenBufferSize(int width, int height);
	
public: 
	// ----- Window console funtions -----
	void BuildConsole(int width, int height);
	
	// ----- Graphic funtions -----


	
	// ----- Sound funtions -----


};


#endif // _GAME_ENGINE_H_