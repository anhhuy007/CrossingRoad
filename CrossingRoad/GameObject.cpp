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

bool Values[16] = { true,false,false,false,false,false,false,true,false,false,false,false,false,false,false,false };
int SetColor(COLORREF color)
{
	CONSOLE_SCREEN_BUFFER_INFOEX info;
	info.cbSize = sizeof(info);
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleScreenBufferInfoEx(hConsole, &info);



	int i, chosen = 17;
	for (i = 0; i < 16; i++) {

		COLORREF a = info.ColorTable[i];

		if (info.ColorTable[i] == color) {
			chosen = i;

			return chosen;
		}

	}
	for (i = 0; i < 16; i++) {

		if (!Values[i]) {
			chosen = i;
			Values[i] = true;
			break;
		}


	}
	if (chosen == 17) {
		throw;
	}
	else {
		info.ColorTable[chosen] = color;
		SetConsoleScreenBufferInfoEx(hConsole, &info);
		return chosen;
	}
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
	int color
) {
	int i = get1DPosition(pixelCoordinate);
	
	buffer[i].Attributes = SetColor(color);
	// square character
	buffer[i].Char.UnicodeChar = 0x2588;
}

