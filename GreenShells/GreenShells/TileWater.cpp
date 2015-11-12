#include "TileWater.h"
#include <iostream>
#include <string>
#include "District.h"
#include "Unit.h"
#include "UnitArcher.h"
#include "UnitSwordsman.h"
#include "UnitSettler.h"

#include "MapFilter.h"
#include "GameSession.h"

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

TileBase* TileWater::Clone()
{
    auto tile = new TileWater{ *this };
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

TileWater* TileWater::Deserialize(boost::property_tree::ptree tileNode, Position pos)
{
    TileWater* tile = new TileWater{ pos };
    tile->m_owner = tileNode.get<int>("<xmlattr>.O");
    tile->m_playerDiscovered = tileNode.get<int>("<xmlattr>.D");
    tile->m_playerSee = tileNode.get<int>("<xmlattr>.S");

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

bool TileWater::CanTraverse(MapFilter filter)
{
    bool result = (filter & ALLOW_WATER) != 0;

    if ((filter & BLOCK_ENEMIES) != 0)
    {
        int currentPlayerID = GameSession::GetInstance().GetCurrentPlayerID();

        if (m_unit != nullptr)
        {
            result &= currentPlayerID == m_unit->GetOwnerID();
        }

        if (m_district != nullptr)
        {
            result &= currentPlayerID == m_district->GetOwnerID();
        }

    }
    return  result;
}

int TileWater::GetTypeAsInt()
{
    return TILE_TYPE;
}