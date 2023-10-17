#include "GameEngine.h"

void GameEngine::bindObjectToScreenBuffer(GameObject object) {
	Graphic::Sprite objectSprite = object.getSprite();

	for (short i = 0; i < object.getHeight(); i += 2) {
		for (short j = 0; j < object.getWidth(); j++) {
			int screenX = i / 2 + object.getPosition().Y;
			int screenY = j + object.getPosition().X;

			//CHAR_INFO pixel = object.getBuffer()[object.get1DPosition({ i, j })];

			Graphic::Pixel abovePixel = objectSprite.getPixel(i, j);
			Graphic::Pixel belowPixel = objectSprite.getPixel(i + 1, j);
			
			CHAR_INFO buffer;
			buffer.Attributes = COLOR::GetColor(belowPixel.color, abovePixel.color);
			buffer.Char.UnicodeChar = 0x2584;

			//cout << screenX << " " << screenY << " " << (int)abovePixel.color << " " << (int)belowPixel.color << endl;

			screenBuffer[screenX * windowSize.x + screenY] = buffer;
		}
		//system("pause");
	}
}

void GameEngine::updateConsole() {
	HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);

	WriteConsoleOutput(
		hStdout,
		screenBuffer,
		{ short(windowSize.x), short(windowSize.y) },
		{ 0, 0 },
		& windowScope
	);
}

GameEngine::GameEngine() {
	fontSize = 6;
	windowSize = { 460, 120 };
	windowScope = { 0, 0, short(windowSize.x - 1), short(windowSize.y - 1) };
	//inputHandle = InputHandle();
	
	// allocate memory for screen buffer
	screenBuffer = new CHAR_INFO[windowSize.x * windowSize.y];	
	for (int i = 0; i < windowSize.x * windowSize.y; i++) {
		screenBuffer[i].Char.UnicodeChar = 0x2588;	// Full block
		screenBuffer[i].Attributes = 0;
	}
}

GameEngine::~GameEngine() {
	delete[] screenBuffer;
}

void GameEngine::BuildConsole() {
	// set the console window size
	system(format("MODE CON COLS={} LINES={}", windowSize.x, windowSize.y).c_str());

	// set window position
	SetWindowPos(
		GetConsoleWindow(),
		HWND_TOP,
		0, 0,
		0, 0,
		SWP_NOSIZE
	);

	// lock the console window size
	SetWindowLong(
		GetConsoleWindow(), 
		GWL_STYLE, 
		GetWindowLong(GetConsoleWindow(), 
		GWL_STYLE) & ~WS_MAXIMIZEBOX & ~WS_SIZEBOX
	);

	// lock buffer size
	SetConsoleScreenBufferSize(
		GetStdHandle(STD_OUTPUT_HANDLE), 
		{ short(windowSize.x), short(windowSize.y) }
	);
	

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

