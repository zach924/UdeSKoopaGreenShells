#pragma once
#include "Position.h"
#include <vector>
#include "Tile.h"

namespace boost
{
    namespace property_tree
    {
        template < class Key, class Data, class KeyCompare >
        class basic_ptree;

        typedef basic_ptree< std::string, std::string, std::less<std::string> > ptree;
    }
}

class Map
{
    static const int ROWS = 64;
    static const int COLUMNS = 64;

    std::vector<std::vector<Tile>> m_tiles;

public:
    Map();
    ~Map();

    void GenerateTiles();

    std::vector<Tile> GetArea(Position position, int distance);

    Tile GetTile(Position);

    boost::property_tree::ptree Serialize();
};

