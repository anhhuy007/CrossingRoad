#pragma once

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
		TextFont font;
		short color = 0;	// from 0 to 15

		std::string GetLetterSpritePath(char letter, TextFont font);
		std::string GetNextWord(int index, std::string ptext);

	public:
		std::vector<COORD> textPositions;
		std::string text;

		Text() : GameObject(nullptr) {};
		Text(
			CrossingRoad* pgame,
			std::string ptext,
			COORD pposition,
			int pwidth,
			int pheight,
			TextFont pfont
		);
		
		Text(
			CrossingRoad* pgame,
			std::string ptext,
			COORD pposition,
			int pwidth,
			int pheight,
			TextFont pfont,
			short pcolor	// from 0 to 15
		);

		// overried methods
		void Update(float elapsedTime) {};
		void Render();
		void UpdateText(std::string ptext);
		void UpdatePosition(COORD pposition); 

		// behaviours
		void SetTextPosition(
			std::string ptext, 
			COORD pposition, 
			int pwidth, 
			int pheight
		);

		void SetTextColor(short pcolor);
	};

	class Button : public GameObject {
	public:
		Button() : GameObject(nullptr) {};
		Button(
			CrossingRoad* pgame,
			std::string ptext,
			std::function<void()> paction,
			COORD pposition = { 0, 0 }
		);

		// behaviours
		void OnTrigger();
		void OnHover();
		void OnNormal();

		// overried methods
		void Update(float elapsedTime) {};
		void Render();

		// attributes
		std::vector<Image> appearance; // 0: normal, 1: chosen, 2: enter
		Text text;
		std::function<void()> action = nullptr;	// on clicked action
		ButtonState state = ButtonState::NORMAL;
	};

	class Dialog : public GameObject {
	public: 
		Dialog() : GameObject(nullptr) {};
		
		Dialog(
			CrossingRoad* pgame,
			std::string ptext,
			std::vector<Widget::Button> &pbuttons,  
			COORD pposition
		);

		Dialog(
			CrossingRoad* pgame,
			Image _pdialog,
			Image _pmessageImage, 
			std::vector<Widget::Button>& pbuttons,
			COORD pposition
		);

		// overried methods
		void Update(float elapsedTime);
		void Render();

		// attributes
		Image dialog;
		Image dialogMessage;
		Widget::Text message;
		std::vector<Widget::Button> buttons;
		int currentButtonIndex = 0;
		COORD position;
		std::vector<COORD> buttonPositions;
		bool enterClicked = false;
		float totalTime = 0;
	};

	int GetWordWidth(std::string word, int letterWidth);

	COORD GetCenterTextPos(
		std::string text, 
		COORD position, 
		int width, 
		int height
	);

	COORD GetMessageImgPos(
		COORD position,
		int width,
		int height, 
		int imgWidth,
		int imgHeight
	);
};
