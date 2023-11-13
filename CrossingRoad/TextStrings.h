#pragma once

#ifndef TEXT_STRING
#define TEXT_STRING

#include <wchar.h>
#include <string>

namespace StringRes {
	const std::wstring const GAME_TITLE = L"Crossing Road";
	const std::wstring const GAME_VERSION = L"1.0.0";
	const std::wstring const INSTRUCTOR = L"Mr. Truong Toan Thing";
}

namespace DrawableRes {
	const std::string spriteFolder = "sprites\\";
	// lane sprites	
	const std::string GrassLane = spriteFolder + "GrassLane.sprite";
	const std::string RoadLane = spriteFolder + "RoadLane.sprite";
	const std::string WaterLane = spriteFolder + "WaterLane.sprite";
	const std::string RoadMarking = spriteFolder + "RoadMarking.sprite";

	// obstacle sprites
	const std::string SmallTree = spriteFolder + "Tree1.sprite";
	const std::string BigTree = spriteFolder + "Tree2.sprite";
	const std::string RaceCarLeft = spriteFolder + "Car2_Left.sprite";
	const std::string RaceCarRight = spriteFolder + "Car2_Right.sprite";
	const std::string CarLeft = spriteFolder + "Car1_Left.sprite";
	const std::string CarRight = spriteFolder + "Car1_Right.sprite";
	const std::string TruckLeft = spriteFolder + "Truck_Left.sprite";
	const std::string TruckRight = spriteFolder + "Truck_Right.sprite";
	// animation sprites
	const std::string animationSprite1 = "Animation1.sprite";
	const std::string animationSprite2 = "Animation2.sprite";
	const std::string animationSprite3 = "Animation3.sprite";
	const std::string animationSprite4 = "Animation4.sprite";
	const std::string animationSprite5 = "Animation5.sprite";
	const std::string animationSprite6 = "Animation6.sprite";
	const std::string animationSprite7 = "Animation7.sprite";
	const std::string animationSprite8 = "Animation8.sprite";
}

#endif // !TEXT_STRING
