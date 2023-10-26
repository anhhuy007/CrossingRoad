#pragma once
class PlayMenu
{
private:
	int MAX_INDEX = 4;

	public:
		enum PlayMenuOption {
		NONE = -1,
		NEW_GAME_P1_MODE = 0,
		NEW_GAME_P2_MODE = 1,
		LOAD_GAME = 2,
		BACK = 3,
		YES = 4,
		NO = 5,
	};

	PlayMenuOption PlayMenuScreen();
	PlayMenuOption NewGameP1Menu();	
	PlayMenuOption NewGameP2Menu();
	PlayMenuOption LoadGameMenu();
	PlayMenuOption BackMenu();

	PlayMenu();
	~PlayMenu();
};

