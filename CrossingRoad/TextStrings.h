#pragma once

#ifndef TEXT_STRING
#define TEXT_STRING

#include <wchar.h>
#include <string>

namespace StringRes {
	const std::wstring const GAME_TITLE = L"Crossing Road";
	const std::wstring const GAME_VERSION = L"1.0.0";
	const std::wstring const INSTRUCTOR = L"Mr. Truong Toan Thinh";
}

namespace DrawableRes {
	const std::string spriteFolder = "sprites\\";

	// lane sprites	
	const std::string GrassLane = spriteFolder + "GrassLane.sprite";
	const std::string RoadLane = spriteFolder + "RoadLane.sprite";
	const std::string WaterLane = spriteFolder + "WaterLane.sprite";
	const std::string SnowLane = spriteFolder + "SnowLane.sprite";
	const std::string RoadMarking = spriteFolder + "RoadMarking.sprite";
	const std::string WhiteBG = spriteFolder + "WhiteBG.sprite";
	const std::string LightBlueBG = spriteFolder + "LightBlueBG.sprite";
	
	// obstacle sprites
	const std::string SmallTree = spriteFolder + "Tree1.sprite";
	const std::string BigTree = spriteFolder + "Tree2.sprite";
	const std::string Car2Left = spriteFolder + "Car2_Left.sprite";
	const std::string Car2Right = spriteFolder + "Car2_Right.sprite";
	const std::string Car1Left = spriteFolder + "Car1_Left.sprite";
	const std::string Car1Right = spriteFolder + "Car1_Right.sprite";
	const std::string TruckLeft = spriteFolder + "Truck_Left.sprite";
	const std::string TruckRight = spriteFolder + "Truck_Right.sprite";
	const std::string Log1 = spriteFolder + "Log1.sprite";
	const std::string Log2 = spriteFolder + "Log2.sprite";
	const std::string Portal = spriteFolder + "Portal.sprite";
	const std::string Grid = spriteFolder + "Grid.sprite";
	const std::string Coin = spriteFolder + "Coin.sprite";
	const std::string Rock = spriteFolder + "Rock.sprite";
	const std::string Rock_Snow = spriteFolder + "Rock_Snow.sprite";
	const std::string PineTree1 = spriteFolder + "PineTree1.sprite";
	const std::string PineTree2 = spriteFolder + "PineTree2.sprite";
	const std::string Gift = spriteFolder + "Gift.sprite";
	const std::string Deer = spriteFolder + "Deer.sprite";
	const std::string Snowman = spriteFolder + "Snowman.sprite";

	// animation sprites
	const std::string animationSprite1 = "Animation1.sprite";
	const std::string animationSprite2 = "Animation2.sprite";
	const std::string animationSprite3 = "Animation3.sprite";
	const std::string animationSprite4 = "Animation4.sprite";
	const std::string animationSprite5 = "Animation5.sprite";
	const std::string animationSprite6 = "Animation6.sprite";

	// button sprites
	const std::string normalButton = "widgets\\NormalButton.sprite";
	const std::string onChosenButton = "widgets\\OnHoverButton.sprite";
	const std::string onEnterButton = "widgets\\OnTriggerButton.sprite";
	const std::string Dialog = "widgets\\Dialog.sprite";
	const std::string DialogButtonNormal = "widgets\\Dialog_Button_Normal.sprite";
	const std::string DialogButtonHover = "widgets\\Dialog_Button_Hover.sprite";
	const std::string DialogButtonTrigger = "widgets\\Dialog_Button_Trigger.sprite";

}

#endif // !TEXT_STRING
