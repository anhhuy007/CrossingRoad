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

void GameEngine::bindObjectToScreenBuffer(GameObject object)
{
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
	cfi.dwFontSize.X = 0;					// Width of each character in the font
	cfi.dwFontSize.Y = fontSize;            // Height
	cfi.FontFamily = FF_DONTCARE;
	cfi.FontWeight = FW_NORMAL;
	std::wcscpy(cfi.FaceName, L"Consolas"); // Choose your font
	SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfi);
}