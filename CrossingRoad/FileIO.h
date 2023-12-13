#pragma once

#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS



#include "Values.h"

#include <string>
#include <iostream>
#include <fstream>
#include <filesystem>

class FileIO {
	const std::string savedGameFolder = "SavedGame\\";
	
public: 
	static bool WriteGameInfo(std::string filename, GameMapInfo gameInfo);
	static bool LoadGameInfo(std::string filename, GameMapInfo& gameInfo);

	static bool WritePlayerOption(std::string filename, PlayerOption& playerOption);

};

#endif // _MSC_VER