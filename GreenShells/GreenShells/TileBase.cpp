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

DistrictBase* TileBase::GetDistrict()
{
    return m_district;
}

void TileBase::SetDistrict(DistrictBase* district)
{
	if (district)
	{
		district->SetPosition(m_position);
	}

    m_district = district;
}

UnitBase * TileBase::GetUnit()
{
    return m_unit;
}

void TileBase::SetUnit(UnitBase* unit)
{
	if (unit)
	{
		unit->SetPosition(m_position);
	}

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

TileBase::TileBase(Position position)
    :m_position(position), m_district(nullptr), m_unit(nullptr), m_owner()
{
}

TileBase* TileBase::Deserialize(boost::property_tree::ptree tileNode, Position pos)
{
    return nullptr;
}

bool TileBase::IsFree()
{
	return !(m_district || m_unit);
}

boost::property_tree::ptree TileBase::Serialize()
{
	boost::property_tree::ptree tileNode;
	tileNode.put("<xmlattr>.TT", GetTypeAsInt());
	tileNode.put("<xmlattr>.O", m_owner);

	if (m_unit)
	{
		        boost::property_tree::ptree unitNode = m_unit->Serialize();
		        tileNode.add_child("U", unitNode);
	}
	if (m_district)
	{
		//        boost::property_tree::ptree districtNode = m_district->Serialize();
		//        tileNode.add_child("D", districtNode);
	}

	return tileNode;
}
