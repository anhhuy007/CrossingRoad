#include "StreetMap.h"

void StreetMap::SetScreenColor() {
	std::vector<int> colors = {
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
			grasslane,
			rand() % 5 + 1
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
	grasslane = Graphic::Sprite(DrawableRes::GrassLane, Overlapped::LAND);
	waterlane = Graphic::Sprite(DrawableRes::WaterLane, Overlapped::LAND);
	roadlane = Graphic::Sprite(DrawableRes::RoadLane, Overlapped::LAND);
	roadMarking = Graphic::Sprite(DrawableRes::RoadMarking, Overlapped::DECORATOR);

	/*Lane* lane = new RoadLane(7, game, roadlane, roadMarking, false);
	lanes.push_back(lane);*/

	for (int i = 0; i < MAXLANE - 2; i++) {
		lanes.push_back(GetNewLane(i, i == 0 ? LaneType::GRASS : lanes[i - 1]->laneType));
	}

	lanes.push_back(new GrassLane(MAXLANE - 2, game, grasslane, 0));
	lanes.push_back(new GrassLane(MAXLANE - 1, game, grasslane, 0));
}

void StreetMap::ScrollUp() {

	lanes.pop_back();
	for (int i = 0; i < lanes.size(); i++) {
		lanes[i]->ScrollUp();
	}

	if (score == 20) {
		// display grass lane with teleport portal
		lanes.insert(lanes.begin(), new GrassLane(0, game, grasslane, 0));
		portal.visible = true;
		portal.setPosition(
			Alignment::getAlignedPosition(
				0,
				9,
				{ -5, 105 },
				Gravity::BOTTOM_CENTER
			)
		);
		portal.lanePos = 0;
	}
	else if (score > 20) {
		lanes.insert(lanes.begin(), new GrassLane(0, game, grasslane, 0));
	}
	else {
		lanes.insert(lanes.begin(), GetNewLane(0, LaneType::GRASS));
	}
	
	if (lanes[0]->laneType == LaneType::ROAD && lanes[1]->laneType == LaneType::ROAD) {
		RoadLane* roadlane = dynamic_cast<RoadLane*>(lanes[1]);
		roadlane->hasRoadMarking = true;
	}
}

Graphic::Sprite grasslane = Graphic::Sprite(DrawableRes::GrassLane);
Graphic::Sprite waterlane = Graphic::Sprite(DrawableRes::WaterLane);
Graphic::Sprite roadlane = Graphic::Sprite(DrawableRes::RoadLane);
Graphic::Sprite roadMarking = Graphic::Sprite(DrawableRes::RoadMarking);
