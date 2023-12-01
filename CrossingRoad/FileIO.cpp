#include "FileIO.h"

const std::string foldername = "SavedGame\\";

bool FileIO::WriteGameInfo(std::string filename, GameMapInfo gameInfo)
{
	// open file
	std::string filepath = foldername + filename;
	std::ofstream ofs(filepath, std::ios::beg | std::ios::binary);

	// error 
	if (!ofs) return 0;

    ofs.write(reinterpret_cast<const char*>(&gameInfo.mapType), sizeof(MapType));
    ofs.write(reinterpret_cast<const char*>(&gameInfo.gameMode), sizeof(GameMode));

    // Write the size of lanesInfo vector
    size_t lanesInfoSize = gameInfo.lanesInfo.size();
    ofs.write(reinterpret_cast<const char*>(&lanesInfoSize), sizeof(size_t));

    // Write each LaneInfo element in the vector
    for (const LaneInfo& lane : gameInfo.lanesInfo) {
        ofs.write(reinterpret_cast<const char*>(&lane.laneType), sizeof(LaneType));
        ofs.write(reinterpret_cast<const char*>(&lane.objectDirection), sizeof(MovingDirection));

        // Write the size of objectsInfo vector
        size_t objectsInfoSize = lane.objectsInfo.size();
        ofs.write(reinterpret_cast<const char*>(&objectsInfoSize), sizeof(size_t));

        // Write each ObjectInfo element in the vector
        ofs.write(reinterpret_cast<const char*>(lane.objectsInfo.data()), objectsInfoSize * sizeof(ObjectInfo));
    }

    ofs.write(reinterpret_cast<const char*>(&gameInfo.playerInfo), sizeof(PlayerInfo));
    ofs.write(reinterpret_cast<const char*>(&gameInfo.endLane), sizeof(int));
    ofs.write(reinterpret_cast<const char*>(&gameInfo.level), sizeof(int));
    ofs.write(reinterpret_cast<const char*>(&gameInfo.score), sizeof(int));
    ofs.write(reinterpret_cast<const char*>(&gameInfo.coin), sizeof(int));

	ofs.close();

	return 1;
}

bool FileIO::LoadGameInfo(std::string filename, GameMapInfo& gameInfo)
{
	std::string filepath = foldername + filename;

	// open file
	std::ifstream ifs(filepath, std::ios::binary);

	if (!ifs) return 0;

    ifs.read(reinterpret_cast<char*>(&gameInfo.mapType), sizeof(MapType));
	ifs.read(reinterpret_cast<char*>(&gameInfo.gameMode), sizeof(GameMode));

	// Read the size of lanesInfo vector
	size_t lanesInfoSize;
	ifs.read(reinterpret_cast<char*>(&lanesInfoSize), sizeof(size_t));

	// Read each LaneInfo element in the vector
	for (size_t i = 0; i < lanesInfoSize; ++i) {
		LaneInfo lane;
		ifs.read(reinterpret_cast<char*>(&lane.laneType), sizeof(LaneType));
		ifs.read(reinterpret_cast<char*>(&lane.objectDirection), sizeof(MovingDirection));

		// Read the size of objectsInfo vector
		size_t objectsInfoSize;
		ifs.read(reinterpret_cast<char*>(&objectsInfoSize), sizeof(size_t));

		// Read each ObjectInfo element in the vector
		lane.objectsInfo.resize(objectsInfoSize);
		ifs.read(reinterpret_cast<char*>(lane.objectsInfo.data()), objectsInfoSize * sizeof(ObjectInfo));

		gameInfo.lanesInfo.push_back(lane);
	}

	ifs.read(reinterpret_cast<char*>(&gameInfo.playerInfo), sizeof(PlayerInfo));
	ifs.read(reinterpret_cast<char*>(&gameInfo.endLane), sizeof(int));
	ifs.read(reinterpret_cast<char*>(&gameInfo.level), sizeof(int));
	ifs.read(reinterpret_cast<char*>(&gameInfo.score), sizeof(int));
	ifs.read(reinterpret_cast<char*>(&gameInfo.coin), sizeof(int));

	ifs.close();
	return 1;
}

