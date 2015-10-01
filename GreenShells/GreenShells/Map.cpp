#include "Map.h"

#include "TileGround.h"
#include "TileMountain.h"
#include "TileWater.h"

#include <fstream>
#include <algorithm>
#include <vector>

#include <boost\property_tree\ptree.hpp>
#include <boost\property_tree\xml_parser.hpp>

Map::Map()
:m_tiles()
{
    for (int i = 0; i < ROWS; i++)
    {
        m_tiles.push_back(std::vector<Tile*>(COLUMNS));
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
        for (int j = 0; j < COLUMNS; ++j)
        {
            char tileType = map.at((i * ROWS) + j);
            switch (tileType)
            {
            case '0':
                m_tiles[i][j] = new TileGround(Position(i, j));
                break;

            case '1':
                m_tiles[i][j] = new TileMountain(Position(i, j));
                break;

            case '2':
            default:
                m_tiles[i][j] = new TileWater(Position(i, j));
                break;
            }
        }
    }
}

std::vector<Tile*> Map::GetArea(Position position, int distance)
{
    std::vector<Tile*> area;

    //find miminum and maximum
    int minCol = std::max(position.X - distance, 0);
    int minRow = std::max(position.Y - distance, 0);
    int maxCol = std::min(position.X + distance, COLUMNS-1);
    int maxRow = std::min(position.Y + distance, ROWS-1);

    for (int i = minCol; i <= maxCol; ++i)
    {
        for (int j = minRow; j <= maxRow; ++j)
        {
            area.push_back(GetTile(Position(i, j)));
        }
    }
    return area;
}

Tile* Map::GetTile(Position position)
{
    return m_tiles[position.X][position.Y];
}

#include <iostream>

boost::property_tree::ptree Map::Serialize()
{
    boost::property_tree::ptree mapNode;

    for (int i = 0; i < ROWS; ++i)
    {
        boost::property_tree::ptree& rowNode = mapNode.add("Row", "");
        rowNode.put("<xmlattr>.Number", i);
        for (int j = 0; j < COLUMNS; ++j)
        {
            boost::property_tree::ptree& tileNode = m_tiles[i][j]->Serialize();
            rowNode.add_child("Tile", tileNode);            
        }
    }
            
    return mapNode;


}

Map Map::Deserialize(boost::property_tree::ptree mapNode)
{
    Map map;
    for each (auto rowNode in mapNode)
    {
        for each(auto tileNode in rowNode.second)
        {
            if (tileNode.first == "Tile")
            {
                Position pos{ tileNode.second.get<int>("<xmlattr>.X"), tileNode.second.get<int>("<xmlattr>.Y") };

                switch (tileNode.second.get<int>("<xmlattr>.Type"))
                {
                case 0:
                    map.m_tiles[pos.X][pos.Y] = TileGround::Deserialize(tileNode.second, pos);
                    break;
                case 1:
                    map.m_tiles[pos.X][pos.Y] = TileMountain::Deserialize(tileNode.second);
                    break;
                case 2:
                    map.m_tiles[pos.X][pos.Y] = TileWater::Deserialize(tileNode.second);
                    break;

                case -1:
                default:
                    // Probably throw error for corrupt file
                    break;
                }
            }
        }
    }

    return map;
}
