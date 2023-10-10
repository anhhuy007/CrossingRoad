#include <iostream>
#include "GameEngine.h"
#include "Colors.h"
#include "Graphic.h"
#include "GameObject.h"

using namespace std;

int main() {
	GameEngine gameEngine;

	gameEngine.BuildConsole();

	SMALL_RECT box = { 20, 20, 50, 50 };
	
	/*gameEngine.displayObject(
		gameEngine.createWrappedObject(10, 10),
		10,
		10,
		Alignment(ALIGNMENT_GRAVITY::CENTRALLY_ALIGNED, 0, 0, 0, 0, box)
	);*/

	int colors[10] = {
		RGB(255, 192, 0),
		RGB(194, 155, 37),
		RGB(237, 214, 142),
		RGB(250, 240, 80),
		RGB(255, 192, 0),
		RGB(194, 155, 37),
		RGB(237, 214, 142),
		RGB(250, 240, 80),
		RGB(255, 192, 0),
		RGB(194, 155, 37)
	};

	GameObject object = GameObject(10, 10);
	for (int i = 0; i < 10; i++) {
		int color = colors[i];
		for (int j = 0; j < 10; j++) {
			object.setPixel(
				{ short(i), short(j) },
				color
			);
		}
	}
	Graphic::displayObject(
		object,
		box,
		Alignment(ALIGNMENT_GRAVITY::TOP_RIGHT, 0, 0, 0, 0, box)
	);

	system("pause>nul");
	
	return 0;
}

//#include <Windows.h>
//#include <string>
//struct Color
//{
//    int r;
//    int g;
//    int b;
//};
//
//void SetBackgroundColor(const Color& aColor)
//{
//    std::string modifier = "\x1b[48;2;" + std::to_string(aColor.r) + ";" + std::to_string(aColor.g) + ";" + std::to_string(aColor.b) + "m";
//    printf(modifier.c_str());
//}
//
//void SetForegroundColor(const Color& aColor)
//{
//    std::string modifier = "\x1b[38;2;" + std::to_string(aColor.r) + ";" + std::to_string(aColor.g) + ";" + std::to_string(aColor.b) + "m";
//    printf(modifier.c_str());
//}
//int main()
//{
//    // Set output mode to handle virtual terminal sequences
//    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
//
//    DWORD dwMode = 0;
//    GetConsoleMode(hOut, &dwMode);
//
//    dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
//    SetConsoleMode(hOut, dwMode);
//
//    SetForegroundColor({ 196, 68, 51 });
//    SetBackgroundColor({ 33 ,105 , 107});
//    printf("Hello World\n");
//
//    system("pause");
//}