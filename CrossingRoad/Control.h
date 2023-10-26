#pragma once
#include "MainMenu.h"
#include "PlayMenu.h"
#include "AboutMenu.h"
#include "SettingMenu.h"

class Control {
	private:
		void Play();
		void MainMenuScreen();

		//Play menu
		void NewGameP1Mode();
		void NewGameP2Mode();
		void ChooseMap();
		void InitNewGame();

		//Setting menu
		void Setting();
		void ChooseCharacter();

		//Init game
		void LoadGame();
		void SaveGame();

		//Leaderboard
		void Leaderboard();

		//About menu
		void About();
		void Credit();
		void GamePlay();

		//Exit
		void ExitGame();
	public:
		//Main menu
		void NavigationController();
		void StartGame();
		void PauseGame();
		void LoadGame();
		void ExitGame();

	

};