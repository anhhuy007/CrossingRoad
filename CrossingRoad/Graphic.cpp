#include "Graphic.h"

void Graphic::gotoXY(short x, short y) {
	static HANDLE h = NULL;
	if (!h) h = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD coord = { x, y };
	SetConsoleCursorPosition(h, coord);
}

void Graphic::displayObject(
	GameObject object,
	SMALL_RECT boxScope,
	Alignment alignment
) {
	HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	SMALL_RECT displayRegion = alignment.getDisplayRegion(object.getWidth(), object.getHeight());

	gotoXY(alignment.boxScope.Left, alignment.boxScope.Top);
	cout << "0";
	gotoXY(alignment.boxScope.Right, alignment.boxScope.Top);
	cout << "1";
	gotoXY(alignment.boxScope.Left, alignment.boxScope.Bottom);
	cout << "2";
	gotoXY(alignment.boxScope.Right, alignment.boxScope.Bottom);
	cout << "3";

	WriteConsoleOutput(
		hStdout,
		object.getBuffer(),
		{ object.getWidth(), object.getHeight() },
		{ 0, 0 },
		&displayRegion
	);
}