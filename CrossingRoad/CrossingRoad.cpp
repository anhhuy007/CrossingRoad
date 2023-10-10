#include <iostream>
#include "GameEngine.h"
#include "Colors.h"

using namespace std;

int main() {

	std::string a = "Hello world, this is a test for colorful.h, which is a library used for printing colorful text";
	COLORREF color = RGB(146, 54, 98);

	//colorful::Write(a, color, colorful::Alignment::Middle);

	return 0;
}