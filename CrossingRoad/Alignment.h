#pragma once

#ifndef ALIGNMENT
#define ALIGNMENT

#include <Windows.h>

using namespace std;

enum class ALIGNMENT_GRAVITY {
	CENTRALLY_ALIGNED, 
	CENTER_HORIZONTAL,
	CENTER_VERTICAL,
	TOP_LEFT,
	TOP_RIGHT,
	BOTTOM_LEFT,
	BOTTOM_RIGHT,
	TOP_CENTER,
	BOTTOM_CENTER,
	DEFAULT,
};


struct Alignment {
	ALIGNMENT_GRAVITY alignment;
	short top, bottom, left, right;
	SMALL_RECT boxScope;

	Alignment(
		ALIGNMENT_GRAVITY alignment,
		short left = 0,
		short top = 0,
		short bottom = 0,
		short right = 0,
		SMALL_RECT boxScope = { 0, 0, 0, 0 }
	) {
		this->alignment = alignment;
		this->top = top;
		this->bottom = bottom;
		this->left = left;
		this->right = right;
		this->boxScope = boxScope;
	}

	COORD getPosition(
		short objectWidth, 
		short objectHeight
	) {
		switch (alignment) {
	
		case ALIGNMENT_GRAVITY::TOP_LEFT:
			return { boxScope.Left, boxScope.Top };

		case ALIGNMENT_GRAVITY::TOP_RIGHT:
			return { short(boxScope.Right - objectWidth), boxScope.Top };

		case ALIGNMENT_GRAVITY::BOTTOM_LEFT:
			return { boxScope.Left, short(boxScope.Bottom - objectHeight) };
			
		case ALIGNMENT_GRAVITY::BOTTOM_RIGHT:
			return { short(boxScope.Right - objectWidth), short(boxScope.Bottom - objectHeight) };

		case ALIGNMENT_GRAVITY::TOP_CENTER:
			return { short((boxScope.Right + boxScope.Left) / 2 - objectWidth / 2), boxScope.Top };

		case ALIGNMENT_GRAVITY::BOTTOM_CENTER:
			return { short((boxScope.Right + boxScope.Left) / 2 - objectWidth / 2), short(boxScope.Bottom - objectHeight) };

		case ALIGNMENT_GRAVITY::CENTER_HORIZONTAL:
			return { short((boxScope.Right + boxScope.Left) / 2 - objectWidth / 2), boxScope.Top };
			
		case ALIGNMENT_GRAVITY::CENTER_VERTICAL:
			return { boxScope.Left, short((boxScope.Bottom + boxScope.Top) / 2 - objectHeight / 2) };

		case ALIGNMENT_GRAVITY::CENTRALLY_ALIGNED:
			return { short((boxScope.Right + boxScope.Left) / 2 - objectWidth / 2), 
					 short((boxScope.Bottom + boxScope.Top) / 2 - objectHeight / 2) };
			
		case ALIGNMENT_GRAVITY::DEFAULT:
			return { boxScope.Left, boxScope.Top };

		default:
			return { boxScope.Left, boxScope.Top };
		}

		return { 0, 0 };
	}

	SMALL_RECT getDisplayRegion(
		short objectWidth, 
		short objectHeight
	) {
		COORD topLeft = getPosition(objectWidth, objectHeight);
		SMALL_RECT displayRegion = { topLeft.X, topLeft.Y, short(topLeft.X + objectWidth), short(topLeft.Y + objectHeight) };
		
		return displayRegion;
	}
};



#endif // !ALIGNMENT

