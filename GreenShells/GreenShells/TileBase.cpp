#include "TileBase.h"
#include "District.h"
#include "Unit.h"
#include "Player.h"
#include <boost\property_tree\ptree.hpp>

TileBase::TileBase(Position position)
    :m_position(position), m_district(nullptr), m_unit(nullptr), m_owner(-1), m_OverlayVisible(), m_playerHaveSeen(0)
{
}

TileBase::~TileBase()
{
    delete m_district;
    delete m_unit;
}

bool TileBase::GetOverlayVisible()
{
    return m_OverlayVisible;
}

void TileBase::SetOverlayVisible(bool visible)
{
    m_OverlayVisible = visible;
}

void TileBase::NotifyNewTurn(int turn)
{
    if (m_district != nullptr)
    {
        m_district->NotifyNewTurn(turn);
    }

    if (m_unit != nullptr)
    {
        m_unit->NotifyNewTurn(turn);
    }
}

Position TileBase::GetPosition()
{
    return m_position;
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

void TileBase::PlayerSee(int playerId)
{
    switch (playerId)
    {
    case 0:
        m_playerHaveSeen |= PLAYER_ONE_SEEN;
        break;
    case 1:
        m_playerHaveSeen |= PLAYER_TWO_SEEN;
        break;
    case 2:
        m_playerHaveSeen |= PLAYER_THREE_SEEN;
        break;
    case 3:
        m_playerHaveSeen |= PLAYER_FOUR_SEEN;
        break;
    case 4:
        m_playerHaveSeen |= PLAYER_FIVE_SEEN;
        break;
    case 5:
        m_playerHaveSeen |= PLAYER_SIX_SEEN;
        break;
    case 6:
        m_playerHaveSeen |= PLAYER_SEVEN_SEEN;
        break;
    case 7:
        m_playerHaveSeen |= PLAYER_EIGHT_SEEN;
        break;
    default:
        break;
    }
}

bool TileBase::IsDiscovered(int playerId)
{
    bool haveSee = false;
    
    switch (playerId)
    {
    case 0:
        haveSee = m_playerHaveSeen & PLAYER_ONE_SEEN;
        break;
    case 1:
        haveSee = m_playerHaveSeen & PLAYER_TWO_SEEN;
        break;
    case 2:
        haveSee = m_playerHaveSeen & PLAYER_THREE_SEEN;
        break;
    case 3:
        haveSee = m_playerHaveSeen & PLAYER_FOUR_SEEN;
        break;
    case 4:
        haveSee = m_playerHaveSeen & PLAYER_FIVE_SEEN;
        break;
    case 5:
        haveSee = m_playerHaveSeen & PLAYER_SIX_SEEN;
        break;
    case 6:
        haveSee = m_playerHaveSeen & PLAYER_SEVEN_SEEN;
        break;
    case 7:
        haveSee = m_playerHaveSeen & PLAYER_EIGHT_SEEN;
        break;
    default:
        break;
    }

    return haveSee;
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
    tileNode.put("<xmlattr>.D", m_playerHaveSeen);

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