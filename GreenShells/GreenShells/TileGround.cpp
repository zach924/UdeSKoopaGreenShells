#include "TileGround.h"
#include <iostream>
#include <string>
#include "District.h"
#include "Unit.h"
#include "UnitArcher.h"
#include "UnitSwordsman.h"

#include "DistrictCityCenter.h"
#include "DistrictFarm.h"

#include <boost\property_tree\ptree.hpp>

void TileGround::LoadTexture()
{
	try
	{
		TileGround::tBase::m_Texture.LoadFromFile("..\\Sprite\\Terrain\\64x64\\Grass.bmp");
	}
	catch (std::exception e)
	{
		std::string msg{ e.what() };
		std::cout << msg << std::endl;
	}
}

TileGround::TileGround(Position position)
:Tile(position)
{
}

TileGround::~TileGround()
{
}

TileGround* TileGround::Deserialize(boost::property_tree::ptree tileNode, Position pos)
{
    TileGround* tile = new TileGround{ pos };
	tile->m_owner = tileNode.get<int>("<xmlattr>.O");

	for each(auto child in tileNode)
	{
		if (child.first == "U")
		{
			switch (child.second.get<int>("<xmlattr>.T"))
			{
			case 0:
				tile->SetUnit(UnitSwordsman::Deserialize(child.second));
				break;
			case 1:
				tile->SetUnit(UnitArcher::Deserialize(child.second));
				break;
			}
		}
		else if (child.first == "D")
		{
			switch (child.second.get<int>("<xmlattr>.T"))
			{
			case 0:
				tile->SetDistrict(DistrictCityCenter::Deserialize(child.second));
				break;
			case 1:
				tile->SetDistrict(DistrictFarm::Deserialize(child.second));
				break;
			}
		}
	}

	return tile;
}

bool TileGround::CanTraverse()
{
	return true;
}

int TileGround::GetTypeAsInt()
{
	return TILE_TYPE;
}
