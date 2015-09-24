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
    boost::property_tree::ptree tileXml;
    boost::property_tree::ptree tileNode = tileXml.add("Tile", "");
    tileNode.put("<xmlattr>.X", m_position.X);
    tileNode.put("<xmlattr>.Y", m_position.Y);

    tileNode.add("Owner", m_owner);

    boost::property_tree::ptree unitNode = m_unit->Serialize();
    boost::property_tree::ptree districtNode = m_district->Serialize();

    tileNode.add_child("Unit", unitNode);
    tileNode.add_child("District", districtNode);

    return tileNode;
}
