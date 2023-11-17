#pragma once

#ifndef WIDGET_H
#define WIDGET_H

#include "GameObject.h"
#include "Values.h"
#include "TextStrings.h"

#include <functional>
#include <string>

#define Image Graphic::Sprite
#define TextSequence std::vector<Image>

namespace Widget {
	class Text : public GameObject {
		TextSequence appearance;
		std::string text;
		TextFont font;
		std::vector<COORD> textPositions;

		std::string GetLetterSpritePath(char letter, TextFont font);

	public:
		Text(CrossingRoad* game) : GameObject(game) {};
		Text(
			CrossingRoad* pgame,
			std::string ptext,
			COORD pposition,
			int pwidth,
			int pheight,
			TextFont pfont
		);

		// overried methods
		void Update(float elapsedTime) {};
		void Render();

		// private functions
	private:
		std::string GetNextWord(int index, std::string ptext);
		int GetWordWidth(std::string word);
	};

	class Button : public GameObject {
	public:
		Button(CrossingRoad* game) : GameObject(game) {};
		Button(
			CrossingRoad* pgame,
			std::string ptext,
			function<void()> paction,
			COORD pposition
		);

		// behaviours
		void OnEnter();
		void OnChosen();
		void OnNormal();

		// overried methods
		void Update(float ElapsedTime) {};
		void Render();

		// attributes
		std::vector<Image> appearance; // 0: normal, 1: chosen, 2: enter
		Text text = Text(game);
		function<void()> action = nullptr;	// on clicked action
		ButtonState state = ButtonState::NORMAL;
	};
};

#endif //!WIDGET_H