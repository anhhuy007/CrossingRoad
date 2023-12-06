#include "ClassicMap.h"

void ClassicMap::SetScreenColor() {
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
	game->SetConsoleColor(colors);
}

Lane* ClassicMap::GetNewLane(
	int laneId, 
	Lane* previousLane
) {
	int randomLane = rand() % 10;

	if (randomLane <= 1) {
		return new GrassLane(
			laneId, 
			game, 
			grasslane,
			rand() % 3 + 1,
			rand() % 2
		);
	}
	else if (randomLane <= 3) {
		MovingDirection direct = MovingDirection::LEFT;

		if (previousLane != nullptr) {
			if (previousLane->laneType == LaneType::WATER) {
				WaterLane* waterlane = dynamic_cast<WaterLane*>(previousLane);

				if (waterlane->direction == MovingDirection::LEFT) {
					direct = MovingDirection::RIGHT;
				}
			}
		}
		
		return new WaterLane(
			laneId, 
			game, 
			direct,
			waterlane
		);
	}
	else if (randomLane == 4) {
		return new RailWayLane(
			laneId, 
			game, 
			railwaylane
		);
	}
	else if (randomLane >= 5) {
		return new RoadLane(
			laneId, 
			game, 
			roadlane,
			roadMarking,
			false	
		);
	}
}

ClassicMap::ClassicMap(
	CrossingRoad* pgame, 
	GameMode pgameMode
) : GameMap(pgame)
{
	gameInfo.mapType = MapType::CLASSIC;
	gameInfo.gameMode = pgameMode;
	gameInfo.level = 1;
	gameInfo.endLane = 20;
}

void ClassicMap::CreateLanes() {
	grasslane = Graphic::Sprite(DrawableRes::GrassLane, Overlapped::LAND);
	waterlane = Graphic::Sprite(DrawableRes::WaterLane, Overlapped::LAND);
	roadlane = Graphic::Sprite(DrawableRes::RoadLane, Overlapped::LAND);
	railwaylane = Graphic::Sprite(DrawableRes::RailWayLane, Overlapped::LAND);
	roadMarking = Graphic::Sprite(DrawableRes::RoadMarking, Overlapped::DECORATOR);


	/*Lane* lane = new RoadLane(7, game, roadlane, roadMarking, false);
	lanes.push_back(lane);*/

	for (int i = 0; i < MAXLANE - 3; i++) {
		lanes.push_back(GetNewLane(i, i == 0 ? nullptr : lanes[i - 1]));
	}

	for (int i = 0; i < lanes.size() - 1; i++) {
		if (lanes[i]->laneType == LaneType::ROAD && lanes[i + 1]->laneType == LaneType::ROAD) {
			RoadLane* roadlane = dynamic_cast<RoadLane*>(lanes[i + 1]);
			roadlane->hasRoadMarking = true;
		}
	}

	lanes.push_back(new GrassLane(MAXLANE - 3, game, grasslane, 0, 0));
	lanes.push_back(new GrassLane(MAXLANE - 2, game, grasslane, 0, 0));
	lanes.push_back(new GrassLane(MAXLANE - 1, game, grasslane, 0, 0));
}

void ClassicMap::ScrollUp() {
	lanes.pop_back();
	for (int i = 0; i < lanes.size(); i++) {
		lanes[i]->ScrollUp();
	}

	if (gameInfo.score == gameInfo.endLane) {
		// display grass lane with teleport portal
		lanes.insert(lanes.begin(), new GrassLane(0, game, grasslane, 0, 0));
		portal.visible = true;
		portal.setPosition(
			Alignment::GetAlignedPosition(
				0,
				9,
				{ -5, 105 },
				Gravity::BOTTOM_CENTER
			)
		);
		portal.lanePos = 0;
	}
	else if (gameInfo.score > gameInfo.endLane) {
		lanes.insert(lanes.begin(), new GrassLane(0, game, grasslane, 0, 0));
	}
	else {
		lanes.insert(lanes.begin(), GetNewLane(0, lanes[0]));
	}
	
	if (lanes[0]->laneType == LaneType::ROAD && lanes[1]->laneType == LaneType::ROAD) {
		RoadLane* roadlane = dynamic_cast<RoadLane*>(lanes[1]);
		roadlane->hasRoadMarking = true;
	}
}
