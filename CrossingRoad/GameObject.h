#pragma once

#ifndef GAME_OBJECT
#define GAME_OBJECT

// ----- STANDARD INCLUDES -----
#include <Windows.h>
#include <wchar.h>
#include <fstream>

// ----- MY CLASS INCLUDES -----
#include "Graphic.h"
#include "CrossingRoad.h"
#include "GameEngine.h"

using namespace std;	

class GameObject {
protected: 
	short width;
	short height;
	COORD position;	// real object position in console (top left coordinate)
	CrossingRoad* game = nullptr;

public:
	GameObject(
		short _width, 
		short _height, 
		COORD _position,
		CrossingRoad* _game
	) {
		this->width = _width;
		this->height = _height;
		this->position = _position;
		this->game = game;
	}
	
	// ----- Getters -----
	short getWidth();
	short getHeight();
	COORD getPosition();

	// ----- Setters -----
	void setPosition(COORD _position);

	// ----- Methods -----
	virtual void Update(float elapsedTime) = 0; 
	virtual void Render() = 0;		// render object in a current state to console
};

#endif // !GAME_OBJECT