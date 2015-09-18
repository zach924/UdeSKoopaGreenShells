#include "Map.h"

#include "TileGround.h"
#include "TileMountain.h"
#include "TileWater.h"

#include <fstream>
#include <algorithm>
#include <vector>


Map::Map()
:m_tiles()
{
	for (int i = 0; i < ROWS; i++)
	{
		m_tiles.push_back(std::vector<Tile>(COLUMNS));
	}
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
				m_tiles[i][j] = TileGround();
				break;

			case '1':
				m_tiles[i][j] = TileMountain();
				break;

			case '2':
			default:
				m_tiles[i][j] = TileWater();
				break;
			}
		}
	}
}

void Map::GetArea(Position position, int distance)
{

}

/*Tile Map::GetTile(Position position)
{
	return 
}*/
