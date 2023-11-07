#pragma once

#include <Windows.h>
#include <iostream>

//#include "Alignment.h" 
#include "Colors.h"
	
#ifndef GRAPHIC_H
#define GRAPHIC_H

namespace Graphic {
	void gotoXY(short x, short y);

	class Pixel {
	public:
		COORD coordinate;
		COLOR::COLOR color;
		int overlapped;

		Pixel(COORD _coordinate, COLOR::COLOR _color);
		Pixel();
	};

	class Sprite {
	private:
		Pixel* pixels;
		int width;
		int height;

	public:
		// ----- Constructors -----
		Sprite(int _width, int _height);
		Sprite();
		Sprite(const char* filename);
		//Sprite(const Sprite& other);

		// ----- Getters -----
		int getWidth();
		int getHeight();
		Pixel getPixel(int i, int j);

		// ----- Setters -----
		void setWidth(int _width);
		void setHeight(int _height);
		void setOverlapped(int _overlapped);

		//Sprite operator=(const Sprite& other);
	};
};

#endif // !GRAPHIC_H
