#include "GameEngine.h"

void GameEngine::DrawRectangle(COORD position, int width, int height, WORD color)
{
	for (int i = position.Y; i < position.Y + height;  i++) {
		for (int j = position.X; j < position.X + width; j++) {
			int index = i * windowSize.x + j;
			screenBuffer[index].Attributes = color;
			screenBuffer[index].Char.UnicodeChar = 0x2588;
		}
	}
}

void GameEngine::Start() {
	// ----- Start game -----
	atomActive = true;
	std::thread thread1 = std::thread(&GameEngine::GameLoop, this);

	thread1.join();
}

void GameEngine::GameLoop() {
	if (!GameCreate()) {
		atomActive = false;
	}

	// timer
	auto time1 = std::chrono::system_clock::now();
	auto time2 = std::chrono::system_clock::now();


	// ----- Game loop -----
	while (atomActive) {
		time2 = std::chrono::system_clock::now();
		auto duration = time2 - time1;
		time1 = time2;
		float elapsedTime = duration.count() / (float) 10000;  // in milliseconds

		// ----- Handle keyboard input -----
		inputHandle = InputHandle::GetKeyBoardState();

		// ----- Handle frame update -----
		if (!GameUpdate(elapsedTime)) {
			atomActive = false;
		}

		// ----- Update game title and FPS -----
		wchar_t s[256];
		swprintf_s(s, 256, L"Crossing Road - FPS: %.2f", (float) 1 / elapsedTime * 10000);
		//swprintf_s(s, 256, L"Crossing Road - FPS: %.2f", elapsedTime);
		SetConsoleTitle(s);

		// ----- Update console screen buffer -----
		UpdateConsole();
		
		// ----- Log text -----
		Graphic::GotToXY(1, 1);
		std::cout << logText << std::endl;

		//std::this_thread::sleep_for(std::chrono::milliseconds(50));
		ClearConsole();
	}
}

void GameEngine::ClearConsole() {
	for (int i = 0; i < windowSize.x * windowSize.y; i++) {
		screenBuffer[i].Char.UnicodeChar = 0x2588;	// Full block
		screenBuffer[i].Attributes = 0;
		overlappedBuffer[i] = 0;
		collisMatrix[i] = 0;
	}

	/*for (int i = 0; i < 460; i++) {
		for (int j = 0; j < 240; j++) {
		}
	}*/
}

void GameEngine::RenderSprite(Graphic::Sprite sprite, COORD position) {
	for (short i = 0; i < sprite.getHeight(); i++) {
		for (short j = 0; j < sprite.getWidth(); j++) {
			int screenX = i + position.Y;
			int screenY = j + position.X;
			int index = screenX * windowSize.x + screenY;

			// check if object is still inside the screen
			if (screenX < 0 || screenX >= windowSize.y || screenY < 0 || screenY >= windowSize.x) continue;

			// get current buffer
			CHAR_INFO buffer = screenBuffer[index];
			
			// get current pixel
			Graphic::Pixel pixel = sprite.getPixel(i, j);
			int color = static_cast<int>(pixel.color);
			int overlapped = pixel.overlapped;

			if (overlapped < overlappedBuffer[index]) continue;

			if (static_cast<COLOR::COLOR>(color) == COLOR::COLOR::TRANSPARENT_) color = buffer.Attributes;

			buffer.Attributes = color;
			buffer.Char.UnicodeChar = 0x2588;
			screenBuffer[index] = buffer;
			overlappedBuffer[index] = overlapped;
		}
		//system("pause");
	}
}

void GameEngine::AddCollisionPoint(COORD point, int type) {
	if (point.X < 0 || point.X >= windowSize.x || point.Y < 0 || point.Y >= windowSize.y) return;

	int index = point.Y * windowSize.x + point.X;
	
	if (collisMatrix[index] > type) return;

	collisMatrix[index] = type;
}

int GameEngine::CheckCollisionPoint(COORD point) {
	if (point.X < 0 || point.X >= windowSize.x || point.Y < 0 || point.Y >= windowSize.y) return 1;
	int index = point.Y * windowSize.x + point.X;

	return collisMatrix[index];
}

void GameEngine::UpdateConsole() {
	CHAR_INFO* consoleBuffer = new CHAR_INFO[windowSize.x * (windowSize.y / 2)];

	// ----- Compress screen buffer height -----
	for (int i = 0; i < windowSize.y; i += 2) {
		for (int j = 0; j < windowSize.x; j++) {
			CHAR_INFO aboveBlock = screenBuffer[i * windowSize.x + j];
			CHAR_INFO belowBlock = screenBuffer[(i + 1) * windowSize.x + j];

			int buffColor = belowBlock.Attributes + aboveBlock.Attributes * 16;
			
			consoleBuffer[(i / 2) * windowSize.x + j] = { 0x2584, (unsigned short)buffColor };
		}
	}

	WriteConsoleOutput(
		hOut,
		consoleBuffer,
		{ short(windowSize.x), short(windowSize.y / 2) },
		{ 0, 0 },
		& windowScope
	);

	delete[] consoleBuffer;
}

GameEngine::GameEngine() {
	hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	fontSize = 6;
	windowSize = { GameScreenLimit::RIGHT, GameScreenLimit::BOTTOM };
	windowScope = { 0, 0, short(windowSize.x - 1), short(windowSize.y - 1) };
	inputHandle = InputHandle::GetKeyBoardState();

	// allocate memory 
	overlappedBuffer = new int[windowSize.x * windowSize.y];
	screenBuffer = new CHAR_INFO[windowSize.x * windowSize.y];
	collisMatrix = new int[windowSize.x * windowSize.y];

	for (int i = 0; i < windowSize.x * windowSize.y; i++) {
		screenBuffer[i].Char.UnicodeChar = 0x2588;	// Full block
		screenBuffer[i].Attributes = 0;
		overlappedBuffer[i] = 0;
		collisMatrix[i] = 0;
	}

	BuildConsole();
}

GameEngine::~GameEngine() {
	delete[] screenBuffer;
	delete[] overlappedBuffer;
	delete[] collisMatrix;
}

void GameEngine::BuildConsole() {
	// set the font size
	CONSOLE_FONT_INFOEX cfi;
	cfi.cbSize = sizeof(cfi);
	cfi.nFont = 0;
	cfi.dwFontSize.X = 0;					// Width of each character in the font
	cfi.dwFontSize.Y = fontSize;            // Height
	cfi.FontFamily = FF_DONTCARE;
	cfi.FontWeight = FW_NORMAL;
	std::wcscpy(cfi.FaceName, L"Consolas"); // Choose your font
	SetCurrentConsoleFontEx(hOut, FALSE, &cfi);

	HWND console = GetConsoleWindow();
	RECT r;
	GetWindowRect(console, &r); //stores the console's current dimensions
	MoveWindow(console, r.left, r.top, 1487, 800, TRUE); // 800 width, 100 height

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

	// diable the cursor
	CONSOLE_CURSOR_INFO cursorInfo;
	GetConsoleCursorInfo(hOut, &cursorInfo);
	cursorInfo.bVisible = false;
	SetConsoleCursorInfo(hOut, &cursorInfo);

	// diable selection
	SetConsoleMode(hOut, ENABLE_EXTENDED_FLAGS | ENABLE_WINDOW_INPUT | ENABLE_MOUSE_INPUT);
}

// ----- define static variables -----
std::atomic<bool> GameEngine::atomActive(false);