#include "TileGround.h"
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
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#ifdef _DEBUG
#define DEBUG_CLIENTBLOCK   new( _CLIENT_BLOCK, __FILE__, __LINE__)
#else
#define DEBUG_CLIENTBLOCK
#endif // _DEBUG

#ifdef _DEBUG
#define new DEBUG_CLIENTBLOCK
#endif
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

TileBase* TileGround::Clone()
{
	auto tile = new TileGround{ *this };
	if (m_district)
	{
		tile->m_district = m_district->Clone();
	}
	if (m_unit)
	{
		tile->m_unit = m_unit->Clone();
	}
	return tile;
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
			case 2:
				tile->SetUnit(UnitSettler::Deserialize(child.second));
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
