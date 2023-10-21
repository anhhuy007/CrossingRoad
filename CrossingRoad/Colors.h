#pragma once

#ifndef COLOR_CONSTANTS
#define COLOR_CONSTANTS

#include <Windows.h>
#include <string>
#include <vector>

namespace COLOR {
	const int TRANSPARENT_ = -1;
	const int BLACK = RGB(0, 0, 0);
	const int BLUE = RGB(0, 0, 255);
	const int GREEN = RGB(6, 85, 53);
	const int YELLOW = RGB(255, 215, 0);
	const int RED = RGB(255, 0, 0);
	const int PURPLE = RGB(128, 0, 128);
	const int BROWN = RGB(165, 42, 42);
	const int LIGHT_GRAY = RGB(192, 192, 192);
	const int ORANGE = RGB(255, 165, 0);
	const int LIGHT_BLUE = RGB(0, 255, 255);
	const int LIGHT_GREEN = RGB(148, 225, 147);
	const int LIGHT_YELLOW = RGB(255, 255, 0);
	const int LIGHT_RED = RGB(255, 115, 115);
	const int PINK = RGB(255, 192, 203);
	const int LIGHT_BROWN = RGB(183, 84, 84);
	const int WHITE	 = RGB(255, 255, 255);

	enum class COLOR {
		TRANSPARENT_ = -1,
		BLACK = 0,
		BLUE = 1,
		GREEN = 2,
		YELLOW = 3,
		RED = 4,
		PURPLE = 5,
		BROWN = 6,
		LIGHT_GRAY = 7,
		ORANGE = 8,
		LIGHT_BLUE = 9,
		LIGHT_GREEN = 10,
		LIGHT_YELLOW = 11,
		LIGHT_RED = 12,
		PINK = 13,
		LIGHT_BROWN = 14,
		WHITE = 15
	};

	int GetColor(
		COLOR foregroundColor,
		COLOR backgroundColor
	);

	void SetConsoleColor(std::vector<int> colors);
	void SetConsoleColor(std::vector<std::string> colors);
	int getRGBFromHex(std::string hexColor);
	
};

#endif // !COLOR_CONSTANTS
