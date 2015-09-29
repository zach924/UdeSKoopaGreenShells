#include "TileGround.h"
#include "District.h"
#include "Unit.h"
#include <boost\property_tree\ptree.hpp>


TileGround::TileGround(Position position)
:Tile(position)
{
}


TileGround::~TileGround()
{
}

boost::property_tree::ptree TileGround::Serialize()
{
    boost::property_tree::ptree tileNode;
    tileNode.put("<xmlattr>.Type", "0");
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

TileGround TileGround::Deserialize(boost::property_tree::ptree tileNode)
{
    return TileGround();
}
