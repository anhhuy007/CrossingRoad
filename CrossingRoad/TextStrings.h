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
	// lane sprites	
	const std::string GrassLane = "GrassLane.sprite";
	const std::string RoadLane = "RoadLane.sprite";
	const std::string WaterLane = "WaterLane.sprite";
	const std::string RoadMarking = "RoadMarking.sprite";

	// obstacle sprites
	const std::string SmallTree = "Tree1.sprite";
	const std::string BigTree = "Tree2.sprite";
	const std::string RaceCarLeft = "Car2_Left.sprite";
	const std::string RaceCarRight = "Car2_Right.sprite";
	const std::string CarLeft = "Car1_Left.sprite";
	const std::string CarRight = "Car1_Right.sprite";
	const std::string TruckLeft = "Truck_Left.sprite";
	const std::string TruckRight = "Truck_Right.sprite";
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
