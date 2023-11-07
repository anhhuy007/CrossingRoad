#include "StreetMap.h"

void StreetMap::CreateLanes() {
	Graphic::Sprite grasslane = Graphic::Sprite("GrassLane.sprite");
	Graphic::Sprite waterlane = Graphic::Sprite("WaterLane.sprite");
	Graphic::Sprite roadlane = Graphic::Sprite("RoadLane.sprite");
	
	grasslane.setOverlapped(Overlapped::LAND);
	waterlane.setOverlapped(Overlapped::LAND);
	roadlane.setOverlapped(Overlapped::LAND);

	/*Lane* lane = new GrassLane(7, game, grasslane);
	lanes.push_back(lane);*/

	for (int i = 0; i < 16; i++) {
		int randomLane = rand() % 3;

		if (randomLane == 0) {
			Lane* lane = new GrassLane(i, game, grasslane);
			lanes.push_back(lane);
		} 
		/*else if (randomLane == 1) {
			Lane* lane = new Lane(i, game, waterlane);
			lanes.push_back(lane);
		}*/
		else if (randomLane == 2) {
			Lane* lane = new RoadLane(i, game, roadlane);
			lanes.push_back(lane);
		}
	}
}