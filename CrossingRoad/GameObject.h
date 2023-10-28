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
	int overlapped;
	CrossingRoad* game = nullptr;

	struct GameSpeed {
		int X_HORIZONTAL = 0;
		int Y_HORIZONTAL = 0;
		int X_VERTICAL = 0;
		int Y_VERTICAL = 0;

		GameSpeed() {
			X_HORIZONTAL = 0;
			Y_HORIZONTAL = 0;
			X_VERTICAL = 0;
			Y_VERTICAL = 0;
		}

		GameSpeed(int xh, int yh, int xv, int yv) {
			X_HORIZONTAL = xh;
			Y_HORIZONTAL = yh;
			X_VERTICAL = xv;
			Y_VERTICAL = yv;
		}
	};

public:
	GameObject(
		int _width,
		int _height,
		COORD _position,
		int _overlapped,
		CrossingRoad* _game
	) {
		this->width = _width;
		this->height = _height;
		this->position = _position;
		this->overlapped = _overlapped;
		this->game = _game;
	}

	GameObject(
		COORD _position,
		int _overlapped,
		CrossingRoad* _game
	) {
		this->position = _position;
		this->overlapped = _overlapped;
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
	virtual void Render() = 0;		// render object in a current state to console
};

#endif // !GAME_OBJECT