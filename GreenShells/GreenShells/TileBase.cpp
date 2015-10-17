#include "TileBase.h"
#include "District.h"
#include "Unit.h"
#include "Player.h"
#include <boost\property_tree\ptree.hpp>

void TileBase::NotifyNewTurn()
{
    if (m_district != nullptr)
    {
        m_district->NotifyNewTurn();
    }

    if (m_unit != nullptr)
    {
        m_unit->NotifyNewTurn();
    }
}

District* TileBase::GetDistrict()
{
    return m_district;
}

void TileBase::SetDistrict(District* district)
{
    m_district = district;
}

Unit * TileBase::GetUnit()
{
    return m_unit;
}

void TileBase::SetUnit(Unit* unit)
{
    m_unit = unit;
}

int TileBase::GetPlayerOwnerId()
{
    return m_owner;
}

void TileBase::SetPlayerOwnerId(int id)
{
    m_owner = id;
}

TileBase::TileBase()
	:m_position(Position(-1,-1)),m_district(nullptr), m_unit(nullptr), m_owner()
{
}

TileBase::TileBase(Position position)
    :m_position(position), m_district(nullptr), m_unit(nullptr), m_owner()
{
}

TileBase* TileBase::Deserialize(boost::property_tree::ptree tileNode, Position pos)
{
    return nullptr;
}