#pragma once

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





	// LEADERBOARD SPRITE
	const std::string leaderboardScreenFolder = "Screen\\leaderboardScreen\\img\\";
	const std::string title = leaderboardScreenFolder + "title.sprite";
	const std::string goldMedal = leaderboardScreenFolder + "gold.sprite";
	const std::string silverMedal = leaderboardScreenFolder + "silver.sprite";
	const std::string bronzeMedal = leaderboardScreenFolder + "bronze.sprite";
	const std::string leaderboardItem = leaderboardScreenFolder + "item.sprite";
	const std::string endlessText = leaderboardScreenFolder + "endlessText.sprite";
	const std::string levelText = leaderboardScreenFolder + "levelText.sprite";
	const std::string leaderboardBg = leaderboardScreenFolder + "leaderboardBg.sprite";

	//--------------------------------------SAVEGAME SCREEN SPRITE-------------------------------
	const std::string saveGameScreenFolder = "Screen\\saveGame\\";
	const std::string saveGameScreenTitleNoShadow = saveGameScreenFolder + "title\\withoutShadow\\withoutShadow";
	const std::string saveGameScreenTitleWithShadow = saveGameScreenFolder + "title\\withShadow\\withShadow";
	//S A V E D G M E withShadow
	const std::string saveGameTitleCharSwithShadow = saveGameScreenTitleWithShadow + "S.Sprite";
	const std::string saveGameTitleCharEwithShadow = saveGameScreenTitleWithShadow + "E.Sprite";
	const std::string saveGameTitleCharAwithShadow = saveGameScreenTitleWithShadow + "A.Sprite";
	const std::string saveGameTitleCharVwithShadow = saveGameScreenTitleWithShadow + "V.Sprite";
	const std::string saveGameTitleCharDwithShadow = saveGameScreenTitleWithShadow + "D.Sprite";
	const std::string saveGameTitleCharGwithShadow = saveGameScreenTitleWithShadow + "G.Sprite";
	const std::string saveGameTitleCharMwithShadow = saveGameScreenTitleWithShadow + "M.Sprite";
	//S A V E D G M withoutShadow
	const std::string saveGameTitleCharSwithoutShadow = saveGameScreenTitleNoShadow + "S.Sprite";
	const std::string saveGameTitleCharEwithoutShadow = saveGameScreenTitleNoShadow + "E.Sprite";
	const std::string saveGameTitleCharAwithoutShadow = saveGameScreenTitleNoShadow + "A.Sprite";
	const std::string saveGameTitleCharVwithoutShadow = saveGameScreenTitleNoShadow + "V.Sprite";
	const std::string saveGameTitleCharDwithoutShadow = saveGameScreenTitleNoShadow + "D.Sprite";
	const std::string saveGameTitleCharGwithoutShadow = saveGameScreenTitleNoShadow + "G.Sprite";
	const std::string saveGameTitleCharMwithoutShadow = saveGameScreenTitleNoShadow + "M.Sprite";


	//--------------------------------------SETTING SCREEN SPRITE-------------------------------
	const std::string settingScreenFolder = "Screen\\settingScreen\\";
	const std::string settingScreenTitleNoShadow = settingScreenFolder + "title\\withoutShadow\\";
	const std::string settingScreenTitleWithShadow = settingScreenFolder + "title\\withShadow\\";
	// S E T I N G withShadow
	const std::string settingTitleCharSwithShadow = settingScreenTitleWithShadow + "S.Sprite";
	const std::string settingTitleCharEwithShadow = settingScreenTitleWithShadow + "E.Sprite";
	const std::string settingTitleCharTwithShadow = settingScreenTitleWithShadow + "T.Sprite";
	const std::string settingTitleCharIwithShadow = settingScreenTitleWithShadow + "I.Sprite";
	const std::string settingTitleCharNwithShadow = settingScreenTitleWithShadow + "N.Sprite";
	const std::string settingTitleCharGwithShadow = settingScreenTitleWithShadow + "G.Sprite";
	// S E T I N G withoutShadow
	const std::string settingTitleCharSwithoutShadow = settingScreenTitleNoShadow + "S.Sprite";
	const std::string settingTitleCharEwithoutShadow = settingScreenTitleNoShadow + "E.Sprite";
	const std::string settingTitleCharTwithoutShadow = settingScreenTitleNoShadow + "T.Sprite";
	const std::string settingTitleCharIwithoutShadow = settingScreenTitleNoShadow + "I.Sprite";
	const std::string settingTitleCharNwithoutShadow = settingScreenTitleNoShadow + "N.Sprite";
	const std::string settingTitleCharGwithoutShadow = settingScreenTitleNoShadow + "G.Sprite";

	//--------------------------------------MENU SCREEN SPRITE-------------------------------
	const std::string menuScreenFolder = "Screen\\menuScreen\\";
	const std::string menuScreenTitleNoShadow = menuScreenFolder + "title\\withoutShadow\\withoutShadow";
	const std::string menuScreenTitleWithShadow = menuScreenFolder + "title\\withShadow\\withShadow";

	// C R O S I N G A D withShadow
	const std::string menuTitleCharCwithShadow = menuScreenTitleWithShadow + "C.Sprite";
	const std::string menuTitleCharRwithShadow = menuScreenTitleWithShadow + "R.Sprite";
	const std::string menuTitleCharOwithShadow = menuScreenTitleWithShadow + "O.Sprite";
	const std::string menuTitleCharSwithShadow = menuScreenTitleWithShadow + "S.Sprite";
	const std::string menuTitleCharIwithShadow = menuScreenTitleWithShadow + "I.Sprite";
	const std::string menuTitleCharNwithShadow = menuScreenTitleWithShadow + "N.Sprite";
	const std::string menuTitleCharGwithShadow = menuScreenTitleWithShadow + "G.Sprite";
	const std::string menuTitleCharAwithShadow = menuScreenTitleWithShadow + "A.Sprite";
	const std::string menuTitleCharDwithShadow = menuScreenTitleWithShadow + "D.Sprite";

	// C R O S I N G A D withoutShadow
	const std::string menuTitleCharCwithoutShadow = menuScreenTitleNoShadow + "C.Sprite";
	const std::string menuTitleCharRwithoutShadow = menuScreenTitleNoShadow + "R.Sprite";
	const std::string menuTitleCharOwithoutShadow = menuScreenTitleNoShadow + "O.Sprite";
	const std::string menuTitleCharSwithoutShadow = menuScreenTitleNoShadow + "S.Sprite";
	const std::string menuTitleCharIwithoutShadow = menuScreenTitleNoShadow + "I.Sprite";
	const std::string menuTitleCharNwithoutShadow = menuScreenTitleNoShadow + "N.Sprite";
	const std::string menuTitleCharGwithoutShadow = menuScreenTitleNoShadow + "G.Sprite";
	const std::string menuTitleCharAwithoutShadow = menuScreenTitleNoShadow + "A.Sprite";
	const std::string menuTitleCharDwithoutShadow = menuScreenTitleNoShadow + "D.Sprite";

	//--------------------------------------SPLASH SCREEN SPRITE-------------------------------
	const std::string splashScreenFolder = "Screen\\splashScreen\\";
	const std::string splashScreenTitleNoShadow = splashScreenFolder + "title\\withoutShadow\\withoutShadow";
	const std::string splashScreenTitleWithShadow = splashScreenFolder + "title\\withShadow\\withShadow";

	// N H O M 1 withShadow
const std::string splashTitleCharNwithShadow = splashScreenTitleWithShadow + "N.Sprite";
const std::string splashTitleCharHwithShadow = splashScreenTitleWithShadow + "H.Sprite";
const std::string splashTitleCharOwithShadow = splashScreenTitleWithShadow + "O.Sprite";
const std::string splashTitleCharMwithShadow = splashScreenTitleWithShadow + "M.Sprite";
const std::string splashTitleChar1withShadow = splashScreenTitleWithShadow + "1.Sprite";
const std::string splashTitleCharACUTEwithShadow = splashScreenTitleWithShadow + "ACUTE.Sprite";

	// N H O M 1 ACUTE withoutShadow
const std::string splashTitleCharNwithoutShadow = splashScreenTitleNoShadow + "N.Sprite";
const std::string splashTitleCharHwithoutShadow = splashScreenTitleNoShadow + "H.Sprite";
const std::string splashTitleCharOwithoutShadow = splashScreenTitleNoShadow + "O.Sprite";
const std::string splashTitleCharMwithoutShadow = splashScreenTitleNoShadow + "M.Sprite";
const std::string splashTitleChar1withoutShadow = splashScreenTitleNoShadow + "1.Sprite";
const std::string splashTitleCharACUTEwithoutShadow = splashScreenTitleNoShadow + "ACUTE.Sprite";



}
