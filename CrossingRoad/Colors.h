#pragma once

#ifndef COLOR_CONSTANTS
#define COLOR_CONSTANTS

#include <Windows.h>
#include <string>

using namespace std;

// some basic colors
enum class COLOR {
	LIGHT_RED = 0xFF474C,
	DARK_RED = 0x7F1D1F,
	LIGHT_GREEN = 0x6BFF6B,
	DARK_GREEN = 0x1F7F1F,
	LIGHT_BLUE = 0x6B6BFF,
	DARK_BLUE = 0x1F1F7F,
	LIGHT_YELLOW = 0xFFFF6B,
	DARK_YELLOW = 0x7F7F1F,
	LIGHT_MAGENTA = 0xFF6BFF,
	DARK_MAGENTA = 0x7F1F7F,
	LIGHT_CYAN = 0x6BFFFF,
	DARK_CYAN = 0x1F7F7F,
	LIGHT_GRAY = 0xBFBFBF,
	DARK_GRAY = 0x7F7F7F,
	LIGHT_BROWN = 0xBFBF7F,
	DARK_BROWN = 0x5C4033,
	BLACK = 0x000000,
	WHITE = 0xFFFFFF,
};

namespace RGB_COLOR {
	COLORREF convertHexToRGB(string colorHex);
	COLORREF ColorRGB(COLOR color);
	COLORREF getAttributeColor(COLORREF color);		// return color's attribute value
};

#endif // !COLOR_CONSTANTS
