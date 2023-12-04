#pragma once

#include <iostream>
#include <fstream>

#include "Colors.h"

namespace Graphic {
	class Pixel {
	public:
		COORD coordinate;
		short color;
		int overlapped;

		Pixel();
		Pixel(COORD _coordinate, short _color);
	};

	class Sprite {
	private:
		Pixel* pixels;
		int width;
		int height;

	public:
		// ----- Constructors -----
		Sprite();
		Sprite(const char* filePath);
		//Sprite(std::string filePath) : Sprite(filePath.c_str()) {};
		Sprite(
			std::string filePath, 
			int poverlapped = 1
		) : Sprite(filePath.c_str()) {
			SetOverlapped(poverlapped);
		};

		// ----- Getters -----
		int GetWidth();
		int GetHeight();
		Pixel GetPixel(int i, int j);

		// ----- Setters -----
		void setWidth(int _width);
		void setHeight(int _height);
		void SetOverlapped(int _overlapped);
		void SetPixelColor(int i, int j, short color);
	};

	void GotToXY(int x, int y);
};
