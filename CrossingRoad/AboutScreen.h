#pragma once

#ifndef ABOUT_SCREEN_H
#define ABOUT_SCREEN_H

#include "Animation.h"
#include "GamePlayer.h"
#include "Widget.h"
#include "MenuWidget.h"
#include "AboutScreen.h"

class AboutScreen : public CrossingRoad::GameScreen {
public:
	AboutScreen(CrossingRoad* game) : GameScreen(game) {};

	// overrided functions 
	bool OnCreate();
	bool OnUpdate(float elapsedTime);
	bool OnDestroy() { return false; };

	Image image;

	//Text
	Widget::Text design = Widget::Text(game, "DESIGNED BY TEAM 11 HCMUS", { 111,73 }, 140, 34, TextFont::NORMAL);
	Widget::Text mssv1 = Widget::Text(game, "22127086 Nguyen Lam Anh Duy", { 115,104 }, 150, 34, TextFont::NORMAL);
	Widget::Text mssv2 = Widget::Text(game, "22127149 Huynh Anh Huy", { 92,150 }, 120, 34, TextFont::NORMAL);
	Widget::Text mssv3 = Widget::Text(game, "22127348 Phan Nguyen Hoang Quan", { 110,180 }, 170, 34, TextFont::NORMAL);
	Widget::Text mssv4 = Widget::Text(game, "Ngo Hoang Nam Hung", { 111,73 }, 170, 34, TextFont::NORMAL);
	Widget::Text instructor = Widget::Text(game, "Instructor Truong Toan Thinh", { 115,104 }, 150, 34, TextFont::NORMAL);
	Widget::Text releasedDate = Widget::Text(game, "Released Date: ", { 92,150 }, 70, 34, TextFont::NORMAL);
	Widget::Text Version = Widget::Text(game, "Ver", { 110,180 }, 70, 34, TextFont::NORMAL);

	MenuWidget aboutMenuWidget = MenuWidget(game);
};

#endif // !ABOUT_SCREEN_H


