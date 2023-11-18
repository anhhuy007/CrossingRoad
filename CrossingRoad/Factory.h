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

#define CollisionPoint std::pair<COORD, int>

class Factory {
public: 
	static std::vector<AnimationSprite> GetPlayerSprite(Player player);
	static std::vector<CollisionPoint> GetObjectCollisionPoints(ObjectType objType);
	static std::vector<CollisionPoint> GetPointsOnLine(
		COORD start,
		COORD end,
		int collisType,
		bool horizontal
	);

	static void sum(
		std::vector<CollisionPoint>& a,
		std::vector<CollisionPoint> b
	);
};

#endif // !FACTORY_H