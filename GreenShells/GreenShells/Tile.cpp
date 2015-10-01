#include "Tile.h"
#include "Player.h"
#include "Unit.h"
#include "District.h"

#include <boost\property_tree\ptree.hpp>

Tile::Tile(Position position)
: m_district(nullptr), m_unit(nullptr), m_owner(-1), m_position(position)
{
}

Tile::Tile()
:m_position(-1,-1)
{
}


Tile::~Tile()
{
}

boost::property_tree::ptree Tile::Serialize()
{
    boost::property_tree::ptree tileNode;
    tileNode.put("<xmlattr>.Type", "0"); // IF we get here (we should not) we will assume its a ground tile
    tileNode.put("<xmlattr>.X", m_position.X);
    tileNode.put("<xmlattr>.Y", m_position.Y);
    tileNode.put("<xmlattr>.Owner", m_owner);

    if (m_unit)
    {
        boost::property_tree::ptree unitNode = m_unit->Serialize();
        tileNode.add_child("Unit", unitNode);
    }
    if (m_district)
    {
        boost::property_tree::ptree districtNode = m_district->Serialize();
        tileNode.add_child("District", districtNode);
    }

    return tileNode;
}

Tile* Tile::Deserialize(boost::property_tree::ptree tileNode, Position pos)
{
    Tile* tile = new Tile{ pos };

    if (pos.X == -1)
    {
        tile->m_position.X = tileNode.get<int>("<xmlattr>.X");
        tile->m_position.Y = tileNode.get<int>("<xmlattr>.Y");
    }
    tile->m_owner = tileNode.get<int>("<xmlattr>.Owner");
    
    for each(auto child in tileNode)
    {
        if (child.first == "Unit")
        {
            // TODO : will need to check how exactly, i think a switch case depend on unit type
        }
        else if (child.first == "District")
        {
            // TODO : will need to check how exactly, i think a switch case depend on district type
        }
    }
    
    return tile;
}
