#pragma once

#ifndef GAME_OBJECT
#define GAME_OBJECT

// ----- STANDARD INCLUDES -----
#include <Windows.h>
#include <wchar.h>

// ----- MY CLASS INCLUDES -----
#include "Colors.h"

using namespace std;

class GameObject {
	
protected: 
	PCHAR_INFO buffer;
	short width;
	short height;
	COORD position; // top left corner

private:
	int get1DPosition(COORD pixelCoordinate);

public:
	GameObject(short _width, short _height);
	~GameObject();

	short getWidth();
	short getHeight();
	PCHAR_INFO getBuffer();

	void setPixelWithCharacter(
		COORD pixelCoordinate, 
		wchar_t character,
		COLOR charColor,
		COLOR backgroundColor
	);

	void setPixel(
		COORD pixelCoordinate,
		int color
	);
};

#endif // !GAME_OBJECT