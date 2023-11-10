#include "StreetMap.h"

void StreetMap::CreateLanes() {
	Graphic::Sprite grasslane = Graphic::Sprite("GrassLane.sprite");
	Graphic::Sprite waterlane = Graphic::Sprite("WaterLane.sprite");
	Graphic::Sprite roadlane = Graphic::Sprite("RoadLane.sprite");
	Graphic::Sprite roadMarking = Graphic::Sprite("RoadMarking.sprite");

	grasslane.setOverlapped(Overlapped::LAND);
	waterlane.setOverlapped(Overlapped::LAND);
	roadlane.setOverlapped(Overlapped::LAND);
	roadMarking.setOverlapped(Overlapped::DECORATOR);

	/*Lane* lane = new GrassLane(7, game, grasslane);
	lanes.push_back(lane);*/

	mapLanes.assign(MAXLANE, "grass");
	for (int i = 0; i < MAXLANE; i++) {
		int randomLane = rand() % 4;

		if (randomLane == 0) {
			Lane* lane = new GrassLane(i, game, grasslane);
			lanes.push_back(lane);
			mapLanes[i] = "grass";
		} 
		else if (randomLane == 1) {
			Lane* lane = new WaterLane(i, game, waterlane);
			lanes.push_back(lane);
			mapLanes[i] = "water";
		}
		else if (randomLane >= 2) {
			bool hasRoadMarking = false;
			if (i > 0) {
				if (mapLanes[i - 1] == "road") hasRoadMarking = true;
			}

			Lane* lane = new RoadLane(i, game, roadlane, roadMarking, hasRoadMarking);
			lanes.push_back(lane);
			mapLanes[i] = "road";
		}
	}
}