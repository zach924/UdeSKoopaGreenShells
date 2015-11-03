#include "TileMountain.h"
#include <string>
#include <iostream>
#include "District.h"
#include "Unit.h"
#include "UnitArcher.h"
#include "UnitSwordsman.h"
#include "UnitSettler.h"

#include "DistrictCityCenter.h"
#include "DistrictFarm.h"

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

TileMountain* TileMountain::Deserialize(boost::property_tree::ptree tileNode, Position pos)
{
    TileMountain* tile = new TileMountain{ pos };
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

bool TileMountain::CanTraverse()
{
	return false;
}

int TileMountain::GetTypeAsInt()
{
	return TILE_TYPE;
}
