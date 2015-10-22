#include "Map.h"

#include "TileGround.h"
#include "TileMountain.h"
#include "TileWater.h"

#include <fstream>
#include <algorithm>
#include <iostream>
#include <vector>
#include <assert.h>
#include <boost\property_tree\ptree.hpp>

Map::Map()
	:m_tiles()
{
	for (int i = 0; i < ROWS; i++)
	{
		m_tiles.push_back(std::vector<TileBase*>(COLUMNS));
	}
}

Map::Map(const Map& source)
	:m_tiles()
{
	for (int i = 0; i < ROWS; i++)
	{
		m_tiles.push_back(std::vector<TileBase*>(COLUMNS));
	}
	for (int i = 0; i < ROWS; ++i)
	{
		for (int j = 0; j < COLUMNS; ++j)
		{
			if (TileGround* ptr = dynamic_cast<TileGround*>(source.m_tiles[i][j]))
			{
				m_tiles[i][j] = new TileGround{ *ptr };
			}
			else if (TileMountain* ptr = dynamic_cast<TileMountain*>(source.m_tiles[i][j]))
			{
				m_tiles[i][j] = new TileMountain{ *ptr };
			}
			else if (TileWater* ptr = dynamic_cast<TileWater*>(source.m_tiles[i][j]))
			{
				m_tiles[i][j] = new TileWater{ *ptr };
			}
		}
	}
}

Map::~Map()
{
	for (auto tileRow : m_tiles)
	{
		for (auto tile : tileRow)
		{
			delete tile;
		}
	}
}

void Map::GenerateTiles()
{
	std::ifstream ifs{ "Ressources\\maps\\FirstMap.txt" };

	assert(ifs.good() && "Make sure you have the ressources folder beside your exe.");

	std::string map((std::istreambuf_iterator<char>(ifs)),
		std::istreambuf_iterator<char>());

	map.erase(std::remove(map.begin(), map.end(), '\n'), map.end());
	for (int i = 0; i < ROWS; ++i)
	{
		for (int j = 0; j < COLUMNS; ++j)
		{
			char tileType = map.at((i * ROWS) + j);
			switch (tileType)
			{
            default:
			case '0':
				m_tiles[i][j] = new TileGround(Position(j, i));
				break;

			case '1':
				m_tiles[i][j] = new TileMountain(Position(j, i));
				break;

			case '2':
				m_tiles[i][j] = new TileWater(Position(j, i));
				break;

			case '3':
				Position position(j, i);
				m_tiles[i][j] = new TileGround(position);
				m_spawnPositions.push_back(position);
				break;
            }
			}
		}
	}

std::vector<Position> Map::GetSpawnPositions()
{
	return m_spawnPositions;
}

std::vector<Position> Map::GetArea(Position position, int distance)
{
	std::vector<Position> area;

	//find miminum and maximum
	int maxCol = position.X + distance;
    int maxRow = position.Y + distance;

	int minCol = position.X - distance;
    if (minCol < 0)
    {
        minCol += COLUMNS;
        maxCol += COLUMNS;
    }
    int minRow = position.Y - distance;
    if (minRow < 0)
    {
        minRow += ROWS;
        maxRow += ROWS;
    }

	for (int i = minCol; i <= maxCol; ++i)
	{
		for (int j = minRow; j <= maxRow; ++j)
		{
			area.push_back(Position(i % COLUMNS, j % ROWS));
		}
	}
	return area;
}

TileBase* Map::GetTile(Position position)
{
	return m_tiles[position.X][position.Y];
}

void Map::NotifyNewturn()
{
	for (std::vector<TileBase*>& tileRow : m_tiles)
	{
		for (TileBase* tile : tileRow)
		{
			tile->NotifyNewTurn();
		}
	}
}

boost::property_tree::ptree Map::Serialize()
{
	boost::property_tree::ptree mapNode;

	boost::property_tree::ptree& spawnListNode = mapNode.add("SPS", "");
	for (int i = 0; i < m_spawnPositions.size(); ++i)
	{
		boost::property_tree::ptree& spawnNode = spawnListNode.add("SP", "");
		spawnNode.put("<xmlattr>.X", m_spawnPositions[i].X);
		spawnNode.put("<xmlattr>.Y", m_spawnPositions[i].Y);
	}

	for (int i = 0; i < ROWS; ++i)
	{
		boost::property_tree::ptree& rowNode = mapNode.add("R", "");
		for (int j = 0; j < COLUMNS; ++j)
		{
			boost::property_tree::ptree& tileNode = m_tiles[i][j]->Serialize();
			rowNode.add_child("T", tileNode);
		}
	}

	return mapNode;
}


bool Map::MoveUnit(int ownerID, Position unitLocation, Position newLocation)
{
	assert(false && "Virtual method is not implemented");
	return false;
}

bool Map::Attack(int ownerID, Position attackerPosition, Position targetPosition)
{
	assert(false && "Virtual method is not implemented");
	return false;
}

