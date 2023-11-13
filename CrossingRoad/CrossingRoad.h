#pragma once

#ifndef _CROSSINGROAD_H_
#define _CROSSINGROAD_H_

#include "GameEngine.h"
#include <string>

class CrossingRoad : public GameEngine {	
public: 
	CrossingRoad() : GameEngine() {};
	
	class GameScreen {
	protected:
		CrossingRoad* game;

	public:
		GameScreen(CrossingRoad* pgame) {
			game = pgame;
		}
		GameScreen() = default;

		// screen life cycle
		virtual bool OnCreate() { return true; }
		virtual bool OnUpdate(float elapsedTime) { return true; }
		virtual bool OnPause() { return false; };	// handle ESC key pressed
		virtual bool OnDestroy() { return false; }

		std::string routeName = "/route";
	};

	// ----- Manage game navigation -----
	class Navigation {
	protected:
		Navigation();
		static GameScreen* currentScreen_;

	public: 
		Navigation(Navigation& other) = delete;
		void operator=(const Navigation&) = delete;

		static void To(std::string route);
		static void To(GameScreen* pscreen);

		static bool OnScreenCreate();
		static bool OnScreenUpdate(float elapsedTime);
		static bool OnScreenPause();
		static bool OnScreenDestroy();

	};	

	void Init();
	bool GameCreate();
	bool GameUpdate(float elapsedTime);
};

#endif // !_CROSSINGROAD_H_