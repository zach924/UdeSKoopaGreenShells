#include "TileGround.h"
#include <iostream>
#include <string>
#include "District.h"

#include "UnitSettler.h"

#include "UnitArcher.h"

#include "UnitSwordsman.h"

#include "UnitAxeman.h"

#include "UnitCannon.h"

#include "MapFilter.h"

#include "DistrictCityCenter.h"
#include "DistrictFarm.h"

#include "GameSession.h"

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
            case UnitSwordsman::UNIT_TYPE:
                tile->SetUnit(UnitSwordsman::Deserialize(child.second));
                break;
            case UnitArcher::UNIT_TYPE:
                tile->SetUnit(UnitArcher::Deserialize(child.second));
                break;
            case UnitSettler::UNIT_TYPE:
                tile->SetUnit(UnitSettler::Deserialize(child.second));
                break;
            case UnitAxeman::UNIT_TYPE:
                tile->SetUnit(UnitAxeman::Deserialize(child.second));
                break;
            case UnitCannon::UNIT_TYPE:
                tile->SetUnit(UnitCannon::Deserialize(child.second));
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

bool TileGround::CanTraverse(MapFilter filter)
{
    bool result = (filter & ALLOW_GROUND) != 0;

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

int TileGround::GetTypeAsInt()
{
    return TILE_TYPE;
}