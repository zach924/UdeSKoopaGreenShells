#include "TileMountain.h"
#include <string>
#include <iostream>
#include "District.h"
#include "Unit.h"
#include <boost\property_tree\ptree.hpp>


TileMountain::TileMountain(Position position)
:Tile(position)
{
}

void TileMountain::LoadTexture()
{
	try
	{
		TileMountain::tBase::m_Texture.LoadFromFile("..\\Sprite\\Terrain\\64x64\\Mountain.bmp");
	}
	catch (std::exception e)
	{
		std::string msg{ e.what() };
		std::cout << msg << std::endl;
	}
}

TileMountain::~TileMountain()
{
}

boost::property_tree::ptree TileMountain::Serialize()
{
    boost::property_tree::ptree tileNode;
    tileNode.put("<xmlattr>.TT", TILE_TYPE);
    tileNode.put("<xmlattr>.O", m_owner);

    if (m_unit)
    {
        boost::property_tree::ptree unitNode = m_unit->Serialize();
        tileNode.add_child("U", unitNode);
    }
    if (m_district)
    {
        boost::property_tree::ptree districtNode = m_district->Serialize();
        tileNode.add_child("D", districtNode);
    }

    return tileNode;
}

TileMountain* TileMountain::Deserialize(boost::property_tree::ptree tileNode, Position pos)
{
    TileMountain* tile = new TileMountain{ pos };

	tile->m_position = pos;
    tile->m_owner = tileNode.get<int>("<xmlattr>.O");

    for each(auto child in tileNode)
    {
        if (child.first == "U")
        {
            // TODO : will need to check how exactly, i think a switch case depend on unit type
        }
        else if (child.first == "D")
        {
            // TODO : will need to check how exactly, i think a switch case depend on district type
        }
    }

    return tile;
}

bool TileMountain::CanTraverse()
{
	return false;
}