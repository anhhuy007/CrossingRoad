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
	const std::string WhiteBG = spriteFolder + "WhiteBG.sprite";
	

	// obstacle sprites
	const std::string SmallTree = spriteFolder + "Tree1.sprite";
	const std::string BigTree = spriteFolder + "Tree2.sprite";
	const std::string RaceCarLeft = spriteFolder + "Car2_Left.sprite";
	const std::string RaceCarRight = spriteFolder + "Car2_Right.sprite";
	const std::string CarLeft = spriteFolder + "Car1_Left.sprite";
	const std::string CarRight = spriteFolder + "Car1_Right.sprite";
	const std::string TruckLeft = spriteFolder + "Truck_Left.sprite";
	const std::string TruckRight = spriteFolder + "Truck_Right.sprite";
	const std::string Log1 = spriteFolder + "Log1.sprite";
	const std::string Log2 = spriteFolder + "Log2.sprite";
	

	// animation sprites
	const std::string animationSprite1 = "Animation1.sprite";
	const std::string animationSprite2 = "Animation2.sprite";
	const std::string animationSprite3 = "Animation3.sprite";
	const std::string animationSprite4 = "Animation4.sprite";
	const std::string animationSprite5 = "Animation5.sprite";

	// button sprites
	const std::string normalButton = "widgets\\NormalButton.sprite";
	const std::string onChosenButton = "widgets\\OnHoverButton.sprite";
	const std::string onEnterButton = "widgets\\OnTriggerButton.sprite";
}

#endif // !TEXT_STRING
