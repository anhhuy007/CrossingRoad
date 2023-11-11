#include "Colors.h"

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
		info.ColorTable[i] = GetRGBFromHex(colors[i]);
	}

	SetConsoleScreenBufferInfoEx(hConsole, &info);
}

int COLOR::GetRGBFromHex(std::string hexColor) {
	int r, g, b;
	sscanf_s(hexColor.c_str(), "%02x%02x%02x", &r, &g, &b); // convert hex string to int
	return RGB(r, g, b);
}