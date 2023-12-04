#pragma once

#include <Windows.h>
#include <string>
#include <vector>

namespace COLOR {
	const int TRANSPARENT_ = -1;

	enum class COLOR {
		TRANSPARENT_ = -1,
	};

	void SetConsoleColor(std::vector<int> colors);
	void SetConsoleColor(std::vector<std::string> colors);
	int GetRGBFromHex(std::string hexColor);
	
};
