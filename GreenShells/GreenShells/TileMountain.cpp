#include "TileMountain.h"
#include "District.h"
#include "Unit.h"
#include <boost\property_tree\ptree.hpp>


TileMountain::TileMountain(Position position)
:Tile(position)
{
}


TileMountain::~TileMountain()
{
}

boost::property_tree::ptree TileMountain::Serialize()
{
    boost::property_tree::ptree tileNode;
    tileNode.put("<xmlattr>.Type", "1");
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

TileMountain TileMountain::Deserialize(boost::property_tree::ptree tileNode)
{
    return TileMountain();
}
