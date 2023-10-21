#include "GameEngine.h"

void GameEngine::GameThread() {
	if (0) {
		atomActive = false;
	}

	// timer
	auto time1 = chrono::system_clock::now();
	auto time2 = chrono::system_clock::now();

	// ----- Game loop -----
	while (atomActive) {
		while (atomActive) {
			time2 = chrono::system_clock::now();
			auto duration = time2 - time1;
			float elapsedTime = duration.count();  // in seconds

			// ----- Handle keyboard input -----
			for (int i = 0; i < 256; i++) {
				inputHandle.keyNewState[i] = GetAsyncKeyState(i);

				// ----- Update input state -----
				inputHandle.arrKeyState[i].isPressed = false;
				inputHandle.arrKeyState[i].isReleased = false;

				if (inputHandle.keyNewState[i] != inputHandle.keyOldState[i]) {
					if (inputHandle.keyNewState[i] & 0x8000) {	// if key is pressed
						inputHandle.arrKeyState[i].isHeld = true;
						inputHandle.arrKeyState[i].isReleased = false;
					}
					else {
						inputHandle.arrKeyState[i].isHeld = false;
						inputHandle.arrKeyState[i].isReleased = true;
					}
				}

				inputHandle.keyOldState[i] = inputHandle.keyNewState[i];
			}

			// ----- Handle frame update -----
			/*if (!GameUpdate(elapsedTime)) {
				atomActive = false;
			}*/

			// ----- Update game title and FPS -----
			wstring title = L"CROSSING ROAD GAME OF GROUP 11 CLC01 - FPS: " + to_wstring(1.0f / elapsedTime);
			SetConsoleTitle(title.c_str());

			// ----- Update console screen buffer -----
			updateConsole();
		}
	}
}

void GameEngine::bindObjectToScreenBuffer(GameObject object) {
	Graphic::Sprite objectSprite = object.getSprite();

	for (short i = 0; i < object.getHeight(); i += 2) {
		for (short j = 0; j < object.getWidth(); j++) {
			int screenX = i / 2 + object.getPosition().Y;
			int screenY = j + object.getPosition().X;


			// check if object is still inside the screen
			//if (screenX < 0 || screenX >= windowSize.x || screenY < 0 || screenY / 2 >= windowSize.y) continue;

			//CHAR_INFO pixel = object.getBuffer()[object.get1DPosition({ i, j })];

			Graphic::Pixel abovePixel = objectSprite.getPixel(i, j);
			Graphic::Pixel belowPixel = objectSprite.getPixel(i + 1, j);
			CHAR_INFO currentSreenBuff = screenBuffer[screenX * windowSize.x + screenY];
			int buffColor = currentSreenBuff.Attributes;
			COLOR::COLOR belowAttribute = static_cast<COLOR::COLOR>(buffColor % 16);
			COLOR::COLOR aboveAttribute = static_cast<COLOR::COLOR>((buffColor - static_cast<int>(belowAttribute)) / 16);
			
			if (abovePixel.color != COLOR::COLOR::TRANSPARENT_) {
				aboveAttribute = abovePixel.color;
			}

			if (belowPixel.color != COLOR::COLOR::TRANSPARENT_) {
				belowAttribute = belowPixel.color;
			}

			CHAR_INFO buffer;
			//buffer.Attributes = COLOR::GetColor(belowPixel.color, abovePixel.color);
			buffer.Attributes = COLOR::GetColor(belowAttribute, aboveAttribute);
			buffer.Char.UnicodeChar = 0x2584;

			//cout << screenX << " " << screenY << " " << (int)aboveAttribute << " " << (int)belowAttribute << endl;

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

// ----- define static variables -----
atomic<bool> GameEngine::atomActive(false);