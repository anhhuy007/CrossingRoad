#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include "Graphic.h"
#include <fstream>

void Graphic::gotoXY(short x, short y) {
	static HANDLE h = NULL;
	if (!h) h = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD coord = { x, y };
	SetConsoleCursorPosition(h, coord);
}

Graphic::Pixel::Pixel(COORD _coordinate, COLOR::COLOR _color) {
	coordinate = _coordinate;
	color = _color;
}

Graphic::Pixel::Pixel() {
	coordinate = { 0, 0 };
	color = COLOR::COLOR::TRANSPARENT_;
}

Graphic::Sprite::Sprite(int _width, int _height) {
	width = _width;
	height = _height;

	// create transparent pixels
	pixels = new Pixel[width * height];
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			pixels[i * width + j] = Pixel();
		}
	}
}

Graphic::Sprite::Sprite() {
	pixels = NULL;
	width = 0;
	height = 0;
}

Graphic::Sprite::Sprite(const char* filename) {
	ifstream ifs(filename, ios::beg);

	if (ifs.fail()) {
		cout << "Cannot open file " << filename << endl;
		return;
	}

	ifs >> width >> height;
	
	int x, y, color;
	// allocate memory
	pixels = new Pixel[width * height + width];

	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			ifs >> y >> x >> color;
			
			// save pixel to pixels array
			pixels[i * width + j] = Pixel({ (short)x, (short)y }, static_cast<COLOR::COLOR>(color));
		}
	}

	ifs.close();
}

int Graphic::Sprite::getWidth()
{
	return width;
}

int Graphic::Sprite::getHeight()
{
	return height;
}

Graphic::Pixel Graphic::Sprite::getPixel(int i, int j) {
	return pixels[i * width + j];
}

void Graphic::Sprite::setHeight(int _height)
{
	height = _height;
}

void Graphic::Sprite::setWidth(int _width)
{
	width = _width;
}

