#include "Map.h"

#include "TileGround.h"
#include "TileMountain.h"
#include "TileWater.h"

#include <fstream>
#include <algorithm>
#include <iostream>
#include <vector>
#include <set>
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
	for (int row = 0; row < ROWS; ++row)
	{
		for (int column = 0; column < COLUMNS; ++column)
		{
			if (TileGround* ptr = dynamic_cast<TileGround*>(source.m_tiles[row][column]))
			{
				m_tiles[row][column] = new TileGround{ *ptr };
			}
			else if (TileMountain* ptr = dynamic_cast<TileMountain*>(source.m_tiles[row][column]))
			{
				m_tiles[row][column] = new TileMountain{ *ptr };
			}
			else if (TileWater* ptr = dynamic_cast<TileWater*>(source.m_tiles[row][column]))
			{
				m_tiles[row][column] = new TileWater{ *ptr };
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
	for (int row = 0; row < ROWS; ++row)
	{
		for (int column = 0; column < COLUMNS; ++column)
		{
			char tileType = map.at((row * ROWS) + column);
			switch (tileType)
			{
            default:
			case '0':
				m_tiles[row][column] = new TileGround(Position(column, row));
				break;

			case '1':
				m_tiles[row][column] = new TileMountain(Position(column, row));
				break;

			case '2':
				m_tiles[row][column] = new TileWater(Position(column, row));
				break;

			case '3':
				Position position(column, row);
				m_tiles[row][column] = new TileGround(position);
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

std::vector<Position> Map::GetArea(Position position, int distance, Filter filter)
{
	std::vector<Position> area;
	std::vector<Position> currentLevel;
	currentLevel.emplace_back(position);
	GetAreaIntern(distance, currentLevel, area, filter);
	//std::vector<Position> area;
	////find miminum and maximum
	//int maxCol = position.X + distance;
 //   int maxRow = position.Y + distance;
	//int minCol = position.X - distance;
 //   if (minCol < 0)
 //   {
 //       minCol += COLUMNS;
 //       maxCol += COLUMNS;
 //   }
 //   int minRow = position.Y - distance;
 //   if (minRow < 0)
 //   {
 //       minRow += ROWS;
 //       maxRow += ROWS;
 //   }
	//for (int i = minCol; i <= maxCol; ++i)
	//{
	//	for (int j = minRow; j <= maxRow; ++j)
	//	{
	//		area.push_back(Position(i % COLUMNS, j % ROWS));
	//	}
	//}
	return area;
}

void Map::GetAreaIntern(int distance, std::vector<Position>& toVisit, std::vector<Position>& alreadyVisited, Filter filter)
{
	if (distance >= 0 )
	{
		std::vector<Position> nextToVisit;

		for (Position pos : toVisit)
		{
			alreadyVisited.emplace_back(pos);

			int topRow = (pos.Row + 1) % ROWS;
			int rightCol = (pos.Column + 1) % COLUMNS;
			int botRow = pos.Row - 1;
			int LeftCol = pos.Column - 1;

			if (botRow < 0)
			{
				botRow = ROWS;
			}

			if (LeftCol < 0)
			{
				LeftCol = ROWS;
			}

			// Find the four tiles
			Position positions[8];

			// Top pos
			positions[0] = Position(pos.Column, topRow);
			// TopRigt pos
			positions[1] = Position(rightCol, topRow);
			// Right pos
			positions[2] = Position(rightCol, pos.Row);
			// BotRight pos
			positions[3] = Position(rightCol, botRow);
			// Bot pos
			positions[4] = Position(pos.Column, botRow);
			// BotLeft pos
			positions[5] = Position(LeftCol, botRow);
			// Left pos
			positions[6] = Position(LeftCol, pos.Row);
			// TopLeft pos
			positions[7] = Position(LeftCol, topRow);

			for (Position position : positions)
			{
				if (!(std::find(alreadyVisited.begin(), alreadyVisited.end(), position) != alreadyVisited.end()))
				{
					if (GetTile(position)->CanTraverse(filter))
					{
						nextToVisit.emplace_back(position);
					}
				}
			}

		} // for()
		GetAreaIntern(distance - 1, nextToVisit, alreadyVisited, filter);
	}
}

TileBase* Map::GetTile(Position position)
{
	return m_tiles[position.Row][position.Column];
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
		spawnNode.put("<xmlattr>.X", m_spawnPositions[i].Column);
		spawnNode.put("<xmlattr>.Y", m_spawnPositions[i].Row);
	}

	for (int row = 0; row < ROWS; ++row)
	{
		boost::property_tree::ptree& rowNode = mapNode.add("R", "");
		for (int column = 0; column < COLUMNS; ++column)
		{
			boost::property_tree::ptree& tileNode = m_tiles[row][column]->Serialize();
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

