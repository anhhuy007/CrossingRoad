#pragma once

#ifndef FACTORY_H
#define FACTORY_H

#include "Values.h"
#include "Graphic.h"
#include <vector>

class Factory {
	static const char* GetSpritePath(const char* spriteFolder);
public: 
	static std::vector<AnimationSprite> GetAnimationSprites(Player player);
};

#endif // !FACTORY_H