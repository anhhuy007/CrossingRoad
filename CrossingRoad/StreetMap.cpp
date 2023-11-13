#include "StreetMap.h"

void StreetMap::SetScreenColor() {
	vector<int> colors = {
		RGB(0, 0, 0),
		RGB(255, 255, 255),
		RGB(174, 222, 102),
		RGB(159, 204, 92),
		RGB(110, 184, 46),
		RGB(12, 67, 57),
		RGB(127, 137, 173),
		RGB(96, 109, 138),
		RGB(72, 78, 94),
		RGB(113, 215, 255),
		RGB(126, 74, 76),
		RGB(255, 112, 51),
		RGB(65, 39, 42),
		RGB(255, 59, 69),
		RGB(176, 40, 49),
		RGB(77, 18, 30)
	};

	COLOR::SetConsoleColor(colors);
}

void StreetMap::CreateLanes() {
	Graphic::Sprite grasslane = Graphic::Sprite(DrawableRes::GrassLane);
	Graphic::Sprite waterlane = Graphic::Sprite(DrawableRes::WaterLane);
	Graphic::Sprite roadlane = Graphic::Sprite(DrawableRes::RoadLane);
	Graphic::Sprite roadMarking = Graphic::Sprite(DrawableRes::RoadMarking);

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