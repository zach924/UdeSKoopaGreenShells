#include "Map.h"
#include <math.h>
#include "TileGround.h"
#include "TileMountain.h"
#include "TileWater.h"
#include "DistrictCityCenter.h"

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

Map::~Map()
{
    for (std::vector<TileBase*> tileRow : m_tiles)
    {
        for (TileBase* tile : tileRow)
        {
            delete tile;
        }
    }
}

void Map::GenerateTiles()
{
    std::ifstream ifs{ "Ressources\\maps\\Islands.txt" };

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

std::map<Position, int> Map::GetArea(Position position, int distance, MapFilter filter, bool stopIfCannotGoFurther)
{
    std::map<Position, int> area;
    if (stopIfCannotGoFurther)
    {
        std::set<Position> currentLevel;
        currentLevel.emplace(position);
        GetAreaIntern(distance, currentLevel, area, filter, distance);
    }
    else
    {
        GetAreaIntern(distance, position, area, filter);
    }
    
    return area;
}

void Map::GetAreaIntern(int distance, std::set<Position>& toVisit, std::map<Position,int>& alreadyVisited, MapFilter filter, const int maxDistance)
{
    if (distance > 0 )
    {
        std::set<Position> nextToVisit;

        for (Position pos : toVisit)
        {
            if (alreadyVisited.emplace(pos, std::abs(maxDistance - distance)).second) // If a real emplaceBack happened
            {

                int topRow = (pos.Row + 1) % ROWS;
                int rightCol = (pos.Column + 1) % COLUMNS;
                int botRow = pos.Row - 1;
                int LeftCol = pos.Column - 1;

                if (botRow < 0)
                {
                    botRow = ROWS - 1;
                }

                if (LeftCol < 0)
                {
                    LeftCol = COLUMNS - 1;
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
                    if (GetTile(position)->CanTraverse(filter))
                    {
                        // Still need to validate if not inside the alreadyVisited position, cause we don't want to visit a position we already visited
                        if(alreadyVisited.find(position) == alreadyVisited.end())
                        {
                            nextToVisit.insert(position);
                        }
                    }
                }
            }

        } // for()
        GetAreaIntern(distance - 1, nextToVisit, alreadyVisited, filter, maxDistance);
    }
    else if (distance == 0)
    {
        // This is the last call, add the lasts ones
        for (Position pos : toVisit)
        {
            alreadyVisited.emplace(pos, std::abs(maxDistance - distance));
        }
    }
}

void Map::GetAreaIntern(int distance, Position position, std::map<Position, int>& areaOut, MapFilter filter)
{
    //find miminum and maximum
    int maxCol = position.Column + distance;
    int maxRow = position.Row + distance;

    int minCol = position.Column - distance;
    if (minCol < 0)
    {
        minCol += COLUMNS;
        maxCol += COLUMNS;
    }
    int minRow = position.Row - distance;
    if (minRow < 0)
    {
        minRow += ROWS;
        maxRow += ROWS;
    }

    for (int i = minCol; i <= maxCol; ++i)
    {
        for (int j = minRow; j <= maxRow; ++j)
        {
            Position posToAdd = Position(i % COLUMNS, j % ROWS);
            if (GetTile(posToAdd)->CanTraverse(filter))
            {
                areaOut.emplace(posToAdd, -1);
            }
        }
    }
 
}

TileBase* Map::GetTile(Position position)
{
    return m_tiles[position.Row][position.Column];
}

void Map::NotifyNewTurn(int turn)
{
    for (std::vector<TileBase*>& tileRow : m_tiles)
    {
        for (TileBase* tile : tileRow)
        {
            tile->NotifyNewTurn(turn);
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