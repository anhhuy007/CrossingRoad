#include "GameObject.h"

GameObject::GameObject(short _width, short _height) {
	width = _width;
	height = _height;
	position = { 0, 0 };
	buffer = new CHAR_INFO[width * height];
}

GameObject::~GameObject() {
}

short GameObject::getWidth() {
	return width;
}

short GameObject::getHeight() {
	return height;
}

PCHAR_INFO GameObject::getBuffer() {
	return buffer;
}

int GameObject::get1DPosition(COORD pixelCoordinate) {
	return pixelCoordinate.X * height + pixelCoordinate.Y;
}

void GameObject::setPixelWithCharacter(
	COORD pixelCoordinate,
	wchar_t character,
	COLOR charColor,
	COLOR backgroundColor
) {
	int i = get1DPosition(pixelCoordinate);
	DWORD attribute = short(charColor) | short(backgroundColor) << 4;
	
	buffer[i].Char.UnicodeChar = character;
	buffer[i].Attributes = FOREGROUND_BLUE | BACKGROUND_RED;
}

void GameObject::setPixel(
	COORD pixelCoordinate,
	string colorHex
) {
	int i = get1DPosition(pixelCoordinate);
	COLORREF color = RGB_COLOR::convertHexToRGB(colorHex);
	
	buffer[i].Attributes = RGB_COLOR::getAttributeColor(color);
	buffer[i].Char.UnicodeChar = 0x2588;	// Full block
}

