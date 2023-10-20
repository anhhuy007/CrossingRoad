#pragma once

#ifndef COLOR_CONSTANTS
#define COLOR_CONSTANTS

#include <Windows.h>
#include <string>

namespace COLOR {
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
};

#endif // !COLOR_CONSTANTS
