#pragma once

#ifndef FACTORY_H
#define FACTORY_H

#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include "Values.h"
#include "Graphic.h"
#include "TextStrings.h"

#include <vector>
#include <string.h>

class Factory {
	static char* GetSpritePath(char* folder, char* fileName);
public: 
	static std::vector<AnimationSprite> GetPlayerSprite(Player player);

};

#endif // !FACTORY_H