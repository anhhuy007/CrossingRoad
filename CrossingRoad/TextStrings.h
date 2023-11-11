#pragma once
#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#ifndef TEXT_STRING
#define TEXT_STRING

#include <windows.h>
#include <wchar.h>
#include <string>

namespace StringRes {
	const std::wstring const GAME_TITLE = L"Crossing Road";
	const std::wstring const GAME_VERSION = L"1.0.0";
	const std::wstring const INSTRUCTOR = L"Mr. Truong Toan Thing";

	// sprite files
	const std::string animationSprite1 = "Animation1.sprite";
	const std::string animationSprite2 = "Animation2.sprite";
	const std::string animationSprite3 = "Animation3.sprite";
	const std::string animationSprite4 = "Animation4.sprite";
	const std::string animationSprite5 = "Animation5.sprite";
	const std::string animationSprite6 = "Animation6.sprite";
	const std::string animationSprite7 = "Animation7.sprite";
	const std::string animationSprite8 = "Animation8.sprite";

}



#endif // !TEXT_STRING
