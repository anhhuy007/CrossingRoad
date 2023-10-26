#pragma once
class MainMenu
{
public:
	enum MenuOption {
		NONE = -1,
		PLAY = 0,
		SETTING = 1,
		LEADERBOARD = 2,
		ABOUT = 3,
		EXIT = 4,
		YES = 5,
		NO = 6,
	};

public:
	MenuOption MenuScreen();
	MenuOption PlayMenu();
	MenuOption SettingMenu();
	MenuOption LeaderboardMenu();
	MenuOption AboutMenu();

	MainMenu();
	~MainMenu();
	
	struct MenuItem {
		int index;
		MenuOption option;
	};
		
protected:
	void menuOptionChanged();
	void drawMenu();
	void drawNormalUI();
	void drawOptionalUI();


};

