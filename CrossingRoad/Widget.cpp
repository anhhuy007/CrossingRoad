#include "Widget.h"
#include "Widget.h"
#include "Widget.h"
#include "Widget.h"
#include "Widget.h"

std::string Widget::Text::GetLetterSpritePath(char letter, TextFont font) {
	std::string path = "alphabet\\";
	switch (font) {
	case TextFont::TITLE:
		path += "title\\";
		break;
	case TextFont::NORMAL:
		path += "normal\\";
		break;
	}

	path = path + letter + ".sprite";

	return path;
}

void Widget::Text::SetText(std::string ptext) {
	text = ptext;
	for (auto& ch : ptext) {
		// get sprite name
		std::string spriteName = GetLetterSpritePath(ch, font);
		appearance.push_back(Image(spriteName));
	}
}
	
//void Widget::Text::Render() {
//	COORD charPos = position;
//	for (auto& char : appearance) {
//		game->RenderSprite(char, charPos);
//		charPos.X += char.getWidth();
//	}
//}

//void Widget::Button::OnEnter(function<void()> action) {
//	// do action
//	action();
//}
//
//void Widget::Button::OnChosen() {
//}
//
//void Widget::Button::OnNormal() {
//}
//
//void Widget::Button::SetText(std::string ptext) {
//}
//
//void Widget::Button::Render() {
//	/*game->RenderSprite(appearance[state].first, position);*/
//}
//