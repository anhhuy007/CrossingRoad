#include "MainMenu.h"
#include "Control.h"
#include <iostream>
#include <vector>

using namespace std;

MainMenu::MenuOption MenuScreen() {

	
	int index = 0;


	vector<MainMenu::MenuItem> menuItems = {
		{ 0,MainMenu::MenuOption::PLAY },
		{ 1,MainMenu::MenuOption::SETTING, },
		{ 2,MainMenu::MenuOption::LEADERBOARD, },
		{ 3,MainMenu::MenuOption::ABOUT, },
		{ 4,MainMenu::MenuOption::EXIT,  }
	};
	return menuItems[index].option;

}

MainMenu::MenuOption PlayMenu() {
	//Draw menu screen
	//Wait for user input
	//return user input
	return MainMenu::MenuOption::PLAY;
}

MainMenu::MenuOption SettingMenu() {
	//Draw menu screen
	//Wait for user input
	//return user input
	return MainMenu::MenuOption::SETTING;
}

MainMenu::MenuOption LeaderboardMenu() {
	//Draw menu screen
	//Wait for user input
	//return user input
	return MainMenu::MenuOption::LEADERBOARD;
}

MainMenu::MenuOption AboutMenu() {
	//Draw menu screen
	//Wait for user input
	//return user input
	return MainMenu::MenuOption::ABOUT;
}

void MainMenu::menuOptionChanged() {
	
}
