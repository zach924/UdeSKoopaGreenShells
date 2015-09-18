#include "Map.h"

#include "TileGround.h"
#include "TileMountain.h"
#include "TileWater.h"

#include <fstream>
#include <algorithm>


Map::Map()
{
}


Map::~Map()
{
}

void Map::GenerateTiles()
{
	std::ifstream ifs{ "Ressources\\maps\\FirstMap.txt" };

	std::string map((std::istreambuf_iterator<char>(ifs)),
		std::istreambuf_iterator<char>());

	map.erase(std::remove(map.begin(), map.end(), '\n'), map.end());
	for (int i = 0; i < ROWS; ++i)
	{
		for (int j = 0; j < ROWS; ++j)
		{
			char tileType = map.at((i * ROWS) + j);
			switch (tileType)
			{
			case '0':
				m_tiles[i][j] = new TileGround();
				break;

			case '1':
				m_tiles[i][j] = new TileMountain();
				break;

			case '2':
			default:
				m_tiles[i][j] = new TileWater();
				break;
			}
		}
	}
}
