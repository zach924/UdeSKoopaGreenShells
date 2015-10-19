#include "TileWater.h"
#include <iostream>
#include <string>
#include "District.h"
#include "Unit.h"

#include "Archer.h"
#include "Swordsman.h"

#include "CityCenter.h"
#include "Farm.h"

#include <boost\property_tree\ptree.hpp>


TileWater::TileWater(Position position)
:Tile(position)
{
}

void TileWater::LoadTexture()
{
	try
	{
		TileWater::tBase::m_Texture.LoadFromFile("..\\Sprite\\Terrain\\64x64\\Water.bmp");
	}
	catch (std::exception e)
	{
		std::string msg{ e.what() };
		std::cout << msg << std::endl;
	}
}


TileWater::~TileWater()
{
}

TileWater* TileWater::Deserialize(boost::property_tree::ptree tileNode, Position pos)
{
    TileWater* tile = new TileWater{ tileNode.get<int>("<xmlattr>.O") };
    tile->m_position = pos;

    for each(auto child in tileNode)
    {
        if (child.first == "U")
        {
			switch (child.second.get<int>("<xmlattr>.T"))
			{
			case 0:
				tile->SetUnit(Swordsman::Deserialize(child.second));
				break;
			case 1:
				tile->SetUnit(Archer::Deserialize(child.second));
				break;
			}            
        }
        else if (child.first == "D")
        {
			switch (child.second.get<int>("<xmlattr>.T"))
			{
			case 0:
				tile->SetDistrict(CityCenter::Deserialize(child.second));
				break;
			case 1:
				tile->SetDistrict(Farm::Deserialize(child.second));
				break;
			}
        }
    }

    return tile;
}

bool TileWater::CanTraverse()
{
	return false;
}

int TileWater::GetTypeAsInt()
{
	return TILE_TYPE;
}
