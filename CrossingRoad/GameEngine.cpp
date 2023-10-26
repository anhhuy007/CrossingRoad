#include "GameEngine.h"

void GameEngine::Start() {
	// ----- Start game -----
	atomActive = true;
	std::thread thread1 = std::thread(&GameEngine::GameLoop, this);

	thread1.join();
}

void GameEngine::GameLoop() {
	/*if (!GameCreate()) {
		atomActive = false;
	}*/

	// timer
	auto time1 = chrono::system_clock::now();
	auto time2 = chrono::system_clock::now();

	// ----- Game loop -----
	while (atomActive) {
		while (atomActive) {
			time2 = chrono::system_clock::now();
			auto duration = time2 - time1;
			time1 = time2;
			float elapsedTime = duration.count();  // in seconds

			// ----- Handle keyboard input -----
			for (int i = 0; i < 256; i++) {
				inputHandle.keyNewState[i] = GetAsyncKeyState(i);

				// ----- Update input state -----
				inputHandle.arrKeyState[i].isPressed = false;
				inputHandle.arrKeyState[i].isReleased = false;

				if (inputHandle.keyNewState[i] != inputHandle.keyOldState[i]) {
					if (inputHandle.keyNewState[i] & 0x8000) {	// if key is pressed
						inputHandle.arrKeyState[i].isPressed = !inputHandle.arrKeyState[i].isHeld;
						inputHandle.arrKeyState[i].isHeld = true;
					}
					else {
						inputHandle.arrKeyState[i].isReleased = true;
						inputHandle.arrKeyState[i].isHeld = false;
					}
				}

				inputHandle.keyOldState[i] = inputHandle.keyNewState[i];
			}

			// ----- Handle frame update -----
			if (!GameUpdate(elapsedTime)) {
				atomActive = false;
			}

			// ----- Update game title and FPS -----
			wchar_t s[256];
			swprintf_s(s, 256, L"Crossing Road - FPS: %.2f", elapsedTime);
			SetConsoleTitle(s);
			
			// ----- Update console screen buffer -----
			UpdateConsole();
			ClearConsole();
		}
	}
}

void GameEngine::ClearConsole() {
	for (int i = 0; i < windowSize.x * windowSize.y; i++) {
		screenBuffer[i].Char.UnicodeChar = 0x2588;	// Full block
		screenBuffer[i].Attributes = 0;
	}
}

void GameEngine::RenderSprite(Graphic::Sprite sprite, COORD position) {
	for (short i = 0; i < sprite.getHeight(); i += 2) {
		for (short j = 0; j < sprite.getWidth(); j++) {
			int screenX = i / 2 + position.Y;
			int screenY = j + position.X;


			// check if object is still inside the screen
			//if (screenX < 0 || screenX >= windowSize.x || screenY < 0 || screenY / 2 >= windowSize.y) continue;

			//CHAR_INFO pixel = object.getBuffer()[object.get1DPosition({ i, j })];

			Graphic::Pixel abovePixel = sprite.getPixel(i, j);
			Graphic::Pixel belowPixel = sprite.getPixel(i + 1, j);
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

void GameEngine::UpdateConsole() {
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
	windowSize = { GameScreenLimit::RIGHT, GameScreenLimit::BOTTOM / 2 };
	windowScope = { 0, 0, short(windowSize.x - 1), short(windowSize.y - 1) };
	inputHandle = InputHandle();
	collistion = new int[windowSize.x * windowSize.y];
	
	// allocate memory for screen buffer
	screenBuffer = new CHAR_INFO[windowSize.x * windowSize.y];	
	for (int i = 0; i < windowSize.x * windowSize.y; i++) {
		screenBuffer[i].Char.UnicodeChar = 0x2588;	// Full block
		screenBuffer[i].Attributes = 0;
		collistion[i] = 0;
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