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
	LEFT_CENTER,
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

		/*cout << blockCoord.X << " " << blockCoord.Y << endl;
		system("pause");*/

		switch (gravity) {
		case Gravity::TOP_LEFT:
			position = { short(blockCoord.X), short(blockCoord.Y) };
			break;
		
		case Gravity::CENTRALLY_ALIGNED:
			position = { short(blockCoord.X + 7), short(blockCoord.Y + 14) };
			break;
		
		case Gravity::BOTTOM_CENTER:
			position = { short(blockCoord.X + 2), short(blockCoord.Y + 24) };
			break;

		case Gravity::LEFT_CENTER:
			position = { short(blockCoord.X - 7), short(blockCoord.Y + 14) };
			break;

		};

		position.X -= objectCenterCoord.X + 13;
		position.Y -= objectCenterCoord.Y + 25;

		return position;
	}

	static COORD getBlockPositionById(
		int laneId,
		int blockId
	) {
		COORD pos;

		pos.X = FIRSTBLOCK.X - 11 * laneId + floor((laneId + 2) / 3) + 24 * blockId;
		pos.Y = FIRSTBLOCK.Y + 21 * laneId + floor((laneId + 2) / 3) + 6 * blockId;

		return pos;
	}

};



#endif // !ALIGNMENT

