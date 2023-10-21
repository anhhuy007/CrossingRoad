#pragma once

#ifndef GAME_OBJECT
#define GAME_OBJECT

// ----- STANDARD INCLUDES -----
#include <Windows.h>
#include <wchar.h>
#include <fstream>

// ----- MY CLASS INCLUDES -----
#include "Colors.h"
#include "Graphic.h"

using namespace std;

class GameObject {
protected: 
	Graphic::Sprite sprite;
	short width;
	short height;
	SMALL_RECT wrappedBox;	// real object position wrapped by rectangle box

public:
	GameObject(short _width, short _height);
	GameObject(Graphic::Sprite _sprite);
	~GameObject();

	// ----- Getters -----
	short getWidth();
	short getHeight();
	SMALL_RECT getWrappedBox();
	COORD getPosition();
	Graphic::Sprite getSprite();

	// ----- Setters -----
	void setPosition(COORD coord);

	// ----- Methods -----
	/*virtual void Update();
	virtual void Render();*/
};

#endif // !GAME_OBJECT