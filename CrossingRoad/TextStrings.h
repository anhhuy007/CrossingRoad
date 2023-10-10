#pragma once
#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#ifndef TEXT_STRING
#define TEXT_STRING

using namespace std;

#include <windows.h>
#include <wchar.h>
#include <string>

const wstring const GAME_TITLE = L"Crossing Road";
const wstring const GAME_VERSION = L"1.0.0";
const wstring const INSTRUCTOR = L"Mr. Truong Toan Thing";

#endif // !TEXT_STRING
