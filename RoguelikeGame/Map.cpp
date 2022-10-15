#include "Map.h"
#include "Game.h"
#include <fstream>
#include "ECS.h"
#include "Components.h"
 
extern Manager manager;

Map::Map(std::string tId, int mapScale, int tileSize) : id(tId), mapScale(mapScale), tileSize(tileSize)
{
	scaledSize = mapScale * tileSize;
}

Map::~Map(){}

void  Map::LoadMap(std::string path, int sizeX, int sizeY)
{
	char c;
	std::fstream mapFile;
	mapFile.open(path);

	int srcX, srcY;

	for (int y = 0; y < sizeY; y++)
	{
		for (int x = 0; x < sizeX; x++)
		{
			mapFile.get(c);
			srcY = atoi(&c) * tileSize;
			
			mapFile.get(c);
			srcX = atoi(&c) * tileSize;

			AddTile(srcX, srcY, x * scaledSize, y * scaledSize);

			mapFile.ignore();
		}
	}	

	mapFile.ignore();

	for (int y = 0; y < sizeY; y++)
	{
		for (int x = 0; x < sizeX; x++)
		{
			mapFile.get(c);
			if (c == '1')
			{
				auto& tcol(manager.AddEntity());
				tcol.AddComponent<ColliderComponent>("Terrain", x * scaledSize, y * scaledSize, scaledSize);
				tcol.AddGroup(Game::GroupLabels::COLLIDER);
			}
			mapFile.ignore();
		}
	}

	mapFile.close();
}

void Map::AddTile(int srcX, int srcY, int xPos, int yPos)
{
	auto& tile(manager.AddEntity());
	tile.AddComponent<TileComponent>(id, srcX, srcY, xPos, yPos, tileSize, mapScale);
	tile.AddGroup(Game::GroupLabels::MAP);
}