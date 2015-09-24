#include "Tile.h"
#include "Player.h"
#include "Unit.h"
#include "District.h"

#include <boost\property_tree\ptree_serialization.hpp>
#include <boost\property_tree\xml_parser.hpp>

Tile::Tile(Position position)
: m_district(nullptr), m_unit(nullptr), m_owner(nullptr), m_position(position)
{
}

Tile::Tile()
:m_position(-1,-1)
{
}


Tile::~Tile()
{
}

boost::property_tree::ptree Tile::ParseXml()
{
    return boost::property_tree::ptree();
}
