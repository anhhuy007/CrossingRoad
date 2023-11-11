#pragma once

#ifndef GRAPHIC_H
#define GRAPHIC_H

#include <Windows.h>
#include <iostream>
#include <fstream>

#include "Colors.h"

namespace Graphic {
	class Pixel {
	public:
		COORD coordinate;
		COLOR::COLOR color;
		int overlapped;

		Pixel();
		Pixel(COORD _coordinate, COLOR::COLOR _color);
	};

	class Sprite {
	private:
		Pixel* pixels;
		int width;
		int height;

	public:
		// ----- Constructors -----
		Sprite();
		Sprite(const char* filename);
		Sprite(std::string filename) : Sprite(filename.c_str()) {};

		// ----- Getters -----
		int getWidth();
		int getHeight();
		Pixel getPixel(int i, int j);

		// ----- Setters -----
		void setWidth(int _width);
		void setHeight(int _height);
		void setOverlapped(int _overlapped);
	};
};

#endif // !GRAPHIC_H
