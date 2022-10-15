#pragma once

#include <string>

class Map
{
public:

	Map(std::string tId, int mapScale, int tileSize);
	~Map();

	void LoadMap(std::string path, int sizeX, int sizeY);
	void AddTile(int srcX, int srcY, int xPos, int yPos);
private:
	std::string id;

	int mapScale;
	int tileSize;

	int scaledSize;
};

