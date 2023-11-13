#pragma once

#ifndef WIDGET_H
#define WIDGET_H

#include "GameObject.h"
#include "Values.h"

#include <functional>
#include <string>

#define Image Graphic::Sprite
#define TextSequence std::vector<Image>

namespace Widget {
	class Text : public GameObject {
		TextSequence appearance;
		std::string text;
		TextFont font;

		std::string GetLetterSpritePath(char letter, TextFont font);

	public:
		Text() = default;
		Text(
			CrossingRoad* game,
			std::string ptext,
			COORD pposition,
			TextFont pfont
		);

		// methods
		void SetText(std::string ptext);

		// overried methods
		void Update(float ElapsedTime);
		void Render();
	};

	//class Button : public GameObject {
	//	Image appearance;
	//	Text text;

	//public: 
	//	Button(CrossingRoad* game) : GameObject(game) {};

	//	// behaviours
	//	void OnEnter(function<void()> action);
	//	void OnChosen();
	//	void OnNormal();


	//	// overried methods
	//	void Update(float ElapsedTime);
	//	void Render();
	//};
};

#endif //!WIDGET_H

