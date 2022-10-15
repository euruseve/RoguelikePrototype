#pragma once

#include <string>

class Map
{
public:

	Map(const char* mapFile, int mapScale, int tileSize);
	~Map();

	void LoadMap(std::string path, int sizeX, int sizeY);
	void AddTile(int srcX, int srcY, int xPos, int yPos);
private:
	const char* mapFile;
	int mapScale;
	int tileSize;

	int scaledSize;
};

