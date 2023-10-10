#pragma once

#ifndef GRAPHIC
#define GRAPHIC

#include <Windows.h>
#include <iostream>

#include "GameObject.h"
#include "Alignment.h"

using namespace std;

namespace Graphic {
	void displayObject(
		GameObject object,
		SMALL_RECT boxScope,
		Alignment alignment
	);

	void gotoXY(short x, short y);
};

#endif // !GRAPHIC
