#pragma once

#ifndef ALIGNMENT
#define ALIGNMENT

#include <Windows.h>
#include "GameObject.h"

enum class Gravity {
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


class Alignment {
public: 
	static COORD getAlignedPosition(
		int laneId,
		int blockId,
		COORD objectCenterCoord,
		Gravity gravity
	) {
		// block: 30x24
		COORD blockCoord = getBlockPositionById(laneId, blockId);
		COORD position = { 0, 0 };

		/*cout << blockCoord.X << " " << blockCoord.Y;
		system("pause");*/

		switch (gravity) {
		case Gravity::TOP_LEFT:
			position = { short(blockCoord.X), short(blockCoord.Y) };
			break;
		
		case Gravity::CENTRALLY_ALIGNED:
			position = { short(blockCoord.X + 6), short(blockCoord.Y + 12) };
			break;
		
		case Gravity::BOTTOM_CENTER:
			return { short(blockCoord.X + 2), short(blockCoord.Y + 24) };
		};

		return { short(position.X - objectCenterCoord.X), short(position.Y - objectCenterCoord.Y) };
	}

	static COORD getBlockPositionById(
		int laneId,
		int blockId
	) {
		return { short(blockId * 24), short((laneId * 24 - 144) + 6 * blockId) };
	}

};



#endif // !ALIGNMENT

