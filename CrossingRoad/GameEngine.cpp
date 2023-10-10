#include "GameEngine.h"

// private:
void GameEngine::SetWindowSize(int width, int height) {
	HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);

	SMALL_RECT WindowSize;
	WindowSize.Top = 0;
	WindowSize.Left = 0;
	WindowSize.Bottom = height;
	WindowSize.Right = width;

	SetConsoleWindowInfo(hStdout, 1, &WindowSize);
}

void GameEngine::SetScreenBufferSize(int width, int height) {
	HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);

	COORD NewSize;
	NewSize.X = width;
	NewSize.Y = height;

	SetConsoleScreenBufferSize(hStdout, NewSize);
}



// public:

SMALL_RECT GameEngine::GetWindowSize() {
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	short columns, rows;
	SMALL_RECT window = { 0, 0, 0, 0 };

	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
	columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;
	rows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;

	window = { 0, 0, columns, rows };

	/*printf("columns: %d\n", columns);
	printf("rows: %d\n", rows);*/

	return window;
}

GameEngine::GameEngine() {
	fontSize = 16;
	windowScope = GetWindowSize();
}

GameEngine::~GameEngine() {

}

void GameEngine::BuildConsole() {
	// set the console window size
	ShowWindow(GetConsoleWindow(), SW_MAXIMIZE);
	HWND consoleWindow = GetConsoleWindow();
	LONG style = GetWindowLong(consoleWindow, GWL_STYLE);
	style = style & ~(WS_MAXIMIZEBOX) & ~(WS_THICKFRAME);
	SetWindowLong(consoleWindow, GWL_STYLE, style);
	ShowScrollBar(GetConsoleWindow(), SB_VERT, 0);

	// set the font size
	CONSOLE_FONT_INFOEX cfi;
	cfi.cbSize = sizeof(cfi);
	cfi.nFont = 0;
	cfi.dwFontSize.X = 0;              // Width of each character in the font
	cfi.dwFontSize.Y = fontSize;            // Height
	cfi.FontFamily = FF_DONTCARE;
	cfi.FontWeight = FW_NORMAL;
	std::wcscpy(cfi.FaceName, L"Consolas"); // Choose your font
	SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfi);
}

PCHAR_INFO GameEngine::createWrappedObject(int width, int height) {
	PCHAR_INFO object = new CHAR_INFO[width * height];

	for (int i = 0; i < width * height; i++) {
		object[i].Char.AsciiChar = '0';
		object[i].Attributes = 1;
	}

	return object;
}

void GameEngine::gotoXY(short x, short y) {
	static HANDLE h = NULL;
	if (!h) h = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD coord = { x, y };
	SetConsoleCursorPosition(h, coord);
}

void GameEngine::displayObject(
	PCHAR_INFO object,
	short objectWidth,
	short objectHeight,
	Alignment alignment
) {
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SMALL_RECT displayRegion = alignment.getDisplayRegion(objectWidth, objectHeight);

	gotoXY(0, 0);
	cout << "displayRegion: " << displayRegion.Left << " " << displayRegion.Top << " " << displayRegion.Right << " " << displayRegion.Bottom << endl;
	cout << "left top: " << displayRegion.Left << " " << displayRegion.Top << endl;

	gotoXY(alignment.boxScope.Left, alignment.boxScope.Top);
	cout << "0";
	gotoXY(alignment.boxScope.Right, alignment.boxScope.Top);
	cout << "1";
	gotoXY(alignment.boxScope.Left, alignment.boxScope.Bottom);
	cout << "2";
	gotoXY(alignment.boxScope.Right, alignment.boxScope.Bottom);
	cout << "3";
	
	WriteConsoleOutput(
		hOut, 
		object, 
		{ objectWidth, objectHeight },
		{0, 0},
		//{ displayRegion.Left, displayRegion.Top },
		&displayRegion
	);
}