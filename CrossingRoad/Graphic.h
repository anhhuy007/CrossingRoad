#pragma once

#include <Windows.h>
#include <iostream>

#include "Alignment.h" 
#include "Colors.h"
	
#ifndef GRAPHIC_H
#define GRAPHIC_H

namespace Graphic {
	void gotoXY(short x, short y);

	class Pixel {
	public:
		COORD coordinate;
		COLOR::COLOR color;

		Pixel(COORD _coordinate, COLOR::COLOR _color);
		Pixel();
	};

	class Sprite {
	private:
		Pixel* pixels;
		short width;
		short height;

	public:
		// ----- Constructors -----
		Sprite(short _width, short _height);
		Sprite();
		Sprite(const char* filename);

		// ----- Getters -----
		short getWidth();
		short getHeight();
		Pixel getPixel(int i, int j);

		// ----- Setters -----
		void setWidth(short _width);
		void setHeight(short _height);
	};
};

#endif // !GRAPHIC_H
