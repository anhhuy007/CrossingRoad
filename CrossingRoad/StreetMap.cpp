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

Lane* StreetMap::GetNewLane(int laneId, LaneType previousLane) {
	int randomLane = rand() % 4;

	if (randomLane == 0) {
		return new GrassLane(
			laneId, 
			game, 
			grasslane
		);
	}
	else if (randomLane == 1) {
		return new WaterLane(
			laneId, 
			game, 
			waterlane
		);
	}
	else if (randomLane >= 2) {
		bool hasRoadMarking = previousLane == LaneType::ROAD ? true : false;

		return new RoadLane(
			laneId, 
			game, 
			roadlane,
			roadMarking,
			hasRoadMarking
		);
	}
}

void StreetMap::CreateLanes() {
	grasslane = Graphic::Sprite(DrawableRes::GrassLane);
	waterlane = Graphic::Sprite(DrawableRes::WaterLane);
	roadlane = Graphic::Sprite(DrawableRes::RoadLane);
	roadMarking = Graphic::Sprite(DrawableRes::RoadMarking);

	grasslane.SetOverlapped(Overlapped::LAND);
	waterlane.SetOverlapped(Overlapped::LAND);
	roadlane.SetOverlapped(Overlapped::LAND);
	roadMarking.SetOverlapped(Overlapped::DECORATOR);

	/*Lane* lane = new RoadLane(7, game, roadlane, roadMarking, false);
	lanes.push_back(lane);*/

	for (int i = 0; i < MAXLANE; i++) {
		lanes.push_back(GetNewLane(i, i == 0 ? LaneType::GRASS : lanes[i - 1]->laneType));
	}
}

void StreetMap::ScrollUp() {
	//lanes.pop_back();
	for (int i = 0; i < lanes.size(); i++) {
		lanes[i]->ScrollUp();
	}
	lanes.insert(lanes.begin(), GetNewLane(0, LaneType::GRASS));
}

Graphic::Sprite grasslane = Graphic::Sprite(DrawableRes::GrassLane);
Graphic::Sprite waterlane = Graphic::Sprite(DrawableRes::WaterLane);
Graphic::Sprite roadlane = Graphic::Sprite(DrawableRes::RoadLane);
Graphic::Sprite roadMarking = Graphic::Sprite(DrawableRes::RoadMarking);
