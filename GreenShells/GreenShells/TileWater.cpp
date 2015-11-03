#include "TileWater.h"
#include <iostream>
#include <string>
#include "District.h"
#include "Unit.h"
#include "UnitArcher.h"
#include "UnitSwordsman.h"
#include "UnitSettler.h"

#include "DistrictCityCenter.h"
#include "DistrictFarm.h"

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
    TileWater* tile = new TileWater{ pos };
	tile->m_owner = tileNode.get<int>("<xmlattr>.O");

    for each(auto child in tileNode)
    {
		if (child.first == "U")
		{
			switch (child.second.get<int>("<xmlattr>.T"))
			{
			case UnitSwordsman::UNIT_TYPE:
				tile->SetUnit(UnitSwordsman::Deserialize(child.second));
				break;
			case UnitArcher::UNIT_TYPE:
				tile->SetUnit(UnitArcher::Deserialize(child.second));
				break;
			case UnitSettler::UNIT_TYPE:
				tile->SetUnit(UnitSettler::Deserialize(child.second));
				break;
			}
		}
		else if (child.first == "D")
		{
			switch (child.second.get<int>("<xmlattr>.T"))
			{
			case DistrictCityCenter::DISTRICT_TYPE:
				tile->SetDistrict(DistrictCityCenter::Deserialize(child.second));
				break;
			case DistrictFarm::DISTRICT_TYPE:
				tile->SetDistrict(DistrictFarm::Deserialize(child.second));
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
