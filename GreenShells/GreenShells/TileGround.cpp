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
    tileNode.put("<xmlattr>.Type", TILE_TYPE);
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

TileGround* TileGround::Deserialize(boost::property_tree::ptree tileNode, Position pos)
{
    TileGround* tile = new TileGround{ pos };

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
            // TODO : When we will have unit to log. Will need to check how exactly, i think a switch case depend on unit type
        }
        else if (child.first == "District")
        {
            // TODO : When district will be done. Will need to check how exactly, i think a switch case depend on district type
        }
    }

    return tile;
}

bool TileGround::CanTraverse()
{
	return true;
}