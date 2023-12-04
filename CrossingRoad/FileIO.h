#pragma once
#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include "Values.h"

#include <string>
#include <iostream>
#include <fstream>

class FileIO {
	const std::string savedGameFolder = "SavedGame\\";
	
public: 
	static bool WriteGameInfo(std::string filename, GameMapInfo gameInfo);
	static bool LoadGameInfo(std::string filename, GameMapInfo& gameInfo);
};
