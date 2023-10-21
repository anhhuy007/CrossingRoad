#include "Colors.h"

int COLOR::GetColor(
	COLOR foregroundColor,
	COLOR backgroundColor
) {
	return (int)foregroundColor | (int)backgroundColor << 4;
}

void COLOR::SetConsoleColor(std::vector<int> colors) {
	CONSOLE_SCREEN_BUFFER_INFOEX info;
	info.cbSize = sizeof(info);
	
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleScreenBufferInfoEx(hConsole, &info);
	
	for (int i = 0; i < colors.size(); i++) {
		info.ColorTable[i] = colors[i];
	}

	SetConsoleScreenBufferInfoEx(hConsole, &info);
}

void COLOR::SetConsoleColor(std::vector<std::string> colors) {
	CONSOLE_SCREEN_BUFFER_INFOEX info;
	info.cbSize = sizeof(info);

	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleScreenBufferInfoEx(hConsole, &info);

	for (int i = 0; i < colors.size(); i++) {
		info.ColorTable[i] = getRGBFromHex(colors[i]);
	}

	SetConsoleScreenBufferInfoEx(hConsole, &info);
}

int COLOR::getRGBFromHex(std::string hexColor) {
	int r, g, b;
	sscanf_s(hexColor.c_str(), "%02x%02x%02x", &r, &g, &b); // convert hex string to int
	return RGB(r, g, b);
}