#include "Colors.h"

#include <iostream>


bool values[16] = { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

COLORREF RGB_COLOR::convertHexToRGB(string colorHex) {

	// format color hex
	for (int i = 0; i < colorHex.size(); i++) {
		if (colorHex[i] >= 'a' && colorHex[i] <= 'z')
			colorHex[i] -= 32;
	}
	
	DWORD r = 0, g = 0, b = 0;
	
	// get r value
	if (colorHex[1] >= '0' && colorHex[1] <= '9') r += (colorHex[1] - '0') * 16;
	else r += (colorHex[1] - 'A' + 10) * 16;
	if (colorHex[2] >= '0' && colorHex[2] <= '9') r += (colorHex[2] - '0');
	else r += (colorHex[2] - 'A' + 10);
	
	// get g value
	if (colorHex[3] >= '0' && colorHex[3] <= '9') g += (colorHex[3] - '0') * 16;
	else g += (colorHex[3] - 'A' + 10) * 16;
	if (colorHex[4] >= '0' && colorHex[4] <= '9') g += (colorHex[4] - '0');
	else g += (colorHex[4] - 'A' + 10);
	
	// get b value
	if (colorHex[5] >= '0' && colorHex[5] <= '9') b += (colorHex[5] - '0') * 16;
	else b += (colorHex[5] - 'A' + 10) * 16;
	if (colorHex[6] >= '0' && colorHex[6] <= '9') b += (colorHex[6] - '0');
	else b += (colorHex[6] - 'A' + 10);

	return RGB(r, g, b);
}

COLORREF RGB_COLOR::getAttributeColor(COLORREF color) {
	CONSOLE_SCREEN_BUFFER_INFOEX info;
	info.cbSize = sizeof(info);
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleScreenBufferInfoEx(hConsole, &info);

	DWORD i, chosen = 17;
	for (i = 0; i < 16; i++) {

		COLORREF a = info.ColorTable[i];

		if (info.ColorTable[i] == color) {
			chosen = i;

			return chosen;
		}

	}
	for (i = 0; i < 16; i++) {
		if (!values[i]) {
			chosen = i;
			values[i] = true;
			break;
		}
	}
	if (chosen == 17) throw;
	else {
		info.ColorTable[chosen] = color;
		SetConsoleScreenBufferInfoEx(hConsole, &info);
		return chosen;
	}
}