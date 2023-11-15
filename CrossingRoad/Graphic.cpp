#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include "Graphic.h"
#include "TextStrings.h"

using namespace Graphic;

Graphic::Pixel::Pixel(COORD _coordinate, COLOR::COLOR _color) {
	coordinate = _coordinate;
	color = _color;
	overlapped = 0;
}

Graphic::Pixel::Pixel() {
	coordinate = { 0, 0 };
	color = COLOR::COLOR::TRANSPARENT_;
	overlapped = 0;
}

Graphic::Sprite::Sprite() {
	pixels = NULL;
	width = 0;
	height = 0;
}

Graphic::Sprite::Sprite(const char* filePath) {
	std::ifstream ifs(filePath, std::ios::beg);

	if (ifs.fail()) {
		std::cerr << "Cannot open file " << filePath;
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


int Graphic::Sprite::getWidth() {
	return width;
}

int Graphic::Sprite::getHeight() {
	return height;
}

Graphic::Pixel Graphic::Sprite::getPixel(int i, int j) {
	return pixels[i * width + j];
}

void Graphic::Sprite::setHeight(int _height) {
	height = _height;
}

void Graphic::Sprite::setOverlapped(int _overlapped) {
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			if (pixels[i * width + j].color != COLOR::COLOR::TRANSPARENT_) {
				pixels[i * width + j].overlapped = _overlapped;
			}
		}
	}
}

void Graphic::Sprite::setWidth(int _width) {
	width = _width;
}


