#include "StreetMap.h"

void StreetMap::CreateLanes() {
	Graphic::Sprite grassLane = Graphic::Sprite("GrassLane.sprite");

	for (int i = 0; i < 5; i++) {
		Lane* lane = new Lane(i + 3, game, grassLane);
		lanes.push_back(lane);
	}
}