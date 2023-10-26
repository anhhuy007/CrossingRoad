#include "Control.h"
#include "MainMenu.h"
#include <iostream>

using namespace std;

void Control::StartGame() {
	// initialize default configuration
	// initialize game setting
	// show menu screen
	Control::NavigationController();
}

void Control::NavigationController() {
	//Draw menu screen
	//Wait for user input
	//return user input
	MainMenu menu;
	MainMenu::MenuOption option = menu.MenuScreen();

	switch (option) {
		case MainMenu::MenuOption::PLAY:
			Control::Play();
			break;
		case MainMenu::MenuOption::SETTING:
			Control::Setting();
			break;
		case MainMenu::MenuOption::LEADERBOARD:
			Control::Leaderboard();
			break;
		case MainMenu::MenuOption::ABOUT:
			Control::About();
			break;
		case MainMenu::MenuOption::EXIT:
			Control::ExitGame();
			break;
	}
}

void Control::Play() {
	//Draw menu screen
	//Wait for user input
	//return user input
	PlayMenu menu;
	PlayMenu::PlayMenuOption option = menu.PlayMenuScreen();

	switch (option) {
	case PlayMenu::PlayMenuOption::NEW_GAME_P1_MODE:
		Control::NewGameP1Mode();
		break;
	case PlayMenu::PlayMenuOption::NEW_GAME_P2_MODE:
		Control::NewGameP2Mode();
		break;
	case PlayMenu::PlayMenuOption::LOAD_GAME:
		Control::LoadGame();
		break;
	}

}

void Control::About() {
	//Draw menu screen
	//Wait for user input
	//return user input
	AboutMenu menu;
	AboutMenu::AboutMenuOption option = menu.AboutMenuScreen();

	switch (option) {
	case AboutMenu::AboutMenuOption::CREDIT:
		Control::Credit();
		break;
	case AboutMenu::AboutMenuOption::GAME_PLAY:
		Control::LoadGame();
		break;
	}
}

void Control::Setting() {
	//Draw menu screen
	//Wait for user input
	//return user input
}

void Control::NewGameP1Mode() {
	//Draw menu screen
	//Wait for user input

	ChooseMap();
	InitNewGame();

}

void Control::NewGameP2Mode() {
	//Draw menu screen
	//Wait for user input

	ChooseCharacter();
	ChooseMap();

	InitNewGame();

}