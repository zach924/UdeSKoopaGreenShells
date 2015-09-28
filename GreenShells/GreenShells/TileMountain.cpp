#include "TileMountain.h"
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
    boost::property_tree::ptree tileXml;
    boost::property_tree::ptree tileNode = tileXml.add("Tile", "");
    tileNode.put("<xmlattr>.X", m_position.X);
    tileNode.put("<xmlattr>.Y", m_position.Y);

//    tileNode.add("Owner", m_owner);

//    boost::property_tree::ptree unitNode = m_unit->Serialize();
//    boost::property_tree::ptree districtNode = m_district->Serialize();
//
//    tileNode.add_child("Unit", unitNode);
//    tileNode.add_child("District", districtNode);

    return tileNode;
}