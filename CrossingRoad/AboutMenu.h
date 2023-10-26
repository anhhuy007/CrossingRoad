#pragma once
class AboutMenu
{
	private:
		int MAX_INDEX = 3;
	public:
		enum AboutMenuOption {
		NONE = -1,
		BACK = 0,
		CREDIT = 1,
		GAME_PLAY = 2,
	};

	AboutMenuOption AboutMenuScreen();
	AboutMenuOption CreditMenu();
	AboutMenuOption GamePlayMenu();

	AboutMenu();
	~AboutMenu();
};

