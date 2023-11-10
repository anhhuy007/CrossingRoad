#pragma once

#ifndef GAME_OBJECT
#define GAME_OBJECT

// ----- STANDARD INCLUDES -----
#include <Windows.h>
#include <wchar.h>
#include <fstream>
#include <string>

// ----- MY CLASS INCLUDES -----
#include "Graphic.h"
#include "CrossingRoad.h"
#include "GameEngine.h"

class GameObject {
protected:
	int width;
	int height;
	COORD position;	// real object position in console (top left coordinate)
	CrossingRoad* game = nullptr;

public:
	GameObject(
		int _width,
		int _height,
		COORD _position,
		CrossingRoad* _game
	) {
		this->width = _width;
		this->height = _height;
		this->position = _position;
		this->game = _game;
	}

	GameObject(
		COORD _position,
		CrossingRoad* _game
	) {
		this->height = 0;
		this->width = 0;
		this->position = _position;
		this->game = _game;
	}

	GameObject(CrossingRoad* _game) {
		this->height = 0;
		this->width = 0;
		this->position = { 0, 0 };
		this->game = _game;
	}
	
	// ----- Getters -----
	int getWidth();
	int getHeight();
	COORD getPosition();

	// ----- Setters -----
	void setPosition(COORD _position);
	void setHeight(int _height);
	void setWidth(int _width);

	// ----- Methods -----
	virtual void Update(float elapsedTime) = 0; 
	virtual void Render() = 0;	// render object in a current state to console
};

#endif // !GAME_OBJECT