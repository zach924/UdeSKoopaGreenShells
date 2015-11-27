#include "TileBase.h"
#include "District.h"
#include "Unit.h"
#include "Player.h"
#include <boost\property_tree\ptree.hpp>

TileBase::TileBase(Position position)
    :m_position(position), m_district(nullptr), m_unit(nullptr), m_owner(-1), m_OverlayVisible(), m_playerDiscovered(0), m_playerSee(0)
{
}

TileBase::~TileBase()
{
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

std::shared_ptr<DistrictBase> TileBase::GetDistrict()
{
    return m_district;
}

void TileBase::SetDistrict(std::shared_ptr<DistrictBase> district)
{
    if (district)
    {
        district->SetPosition(m_position);
    }

    m_district = district;
}

std::shared_ptr<UnitBase> TileBase::GetUnit()
{
    return m_unit;
}

void TileBase::SetUnit(std::shared_ptr<UnitBase> unit)
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

void TileBase::PlayerDiscover(int playerId)
{
    switch (playerId)
    {
    case 0:
        m_playerDiscovered |= PLAYER_ONE_SEEN;
        break;
    case 1:
        m_playerDiscovered |= PLAYER_TWO_SEEN;
        break;
    case 2:
        m_playerDiscovered |= PLAYER_THREE_SEEN;
        break;
    case 3:
        m_playerDiscovered |= PLAYER_FOUR_SEEN;
        break;
    case 4:
        m_playerDiscovered |= PLAYER_FIVE_SEEN;
        break;
    case 5:
        m_playerDiscovered |= PLAYER_SIX_SEEN;
        break;
    case 6:
        m_playerDiscovered |= PLAYER_SEVEN_SEEN;
        break;
    case 7:
        m_playerDiscovered |= PLAYER_EIGHT_SEEN;
        break;
    default:
        assert(false && "Select a player from 0 to 7 to discover a tile.");
        break;
    }
}

bool TileBase::IsDiscovered(int playerId)
{
    bool isDiscover = false;
    
    switch (playerId)
    {
    case 0:
        isDiscover = (m_playerDiscovered & PLAYER_ONE_SEEN) != 0;
        break;
    case 1:
        isDiscover = (m_playerDiscovered & PLAYER_TWO_SEEN) != 0;
        break;
    case 2:
        isDiscover = (m_playerDiscovered & PLAYER_THREE_SEEN) != 0;
        break;
    case 3:
        isDiscover = (m_playerDiscovered & PLAYER_FOUR_SEEN) != 0;
        break;
    case 4:
        isDiscover = (m_playerDiscovered & PLAYER_FIVE_SEEN) != 0;
        break;
    case 5:
        isDiscover = (m_playerDiscovered & PLAYER_SIX_SEEN) != 0;
        break;
    case 6:
        isDiscover = (m_playerDiscovered & PLAYER_SEVEN_SEEN) != 0;
        break;
    case 7:
        isDiscover = (m_playerDiscovered & PLAYER_EIGHT_SEEN) != 0;
        break;
    default:
        assert(false && "Select a player from 0 to 7 to know if has discover a tile.");
        break;
    }

    return isDiscover;
}

void TileBase::PlayerSee(int playerId)
{
    switch (playerId)
    {
    case 0:
        m_playerSee |= PLAYER_ONE_SEEN;
        break;
    case 1:
        m_playerSee |= PLAYER_TWO_SEEN;
        break;
    case 2:
        m_playerSee |= PLAYER_THREE_SEEN;
        break;
    case 3:
        m_playerSee |= PLAYER_FOUR_SEEN;
        break;
    case 4:
        m_playerSee |= PLAYER_FIVE_SEEN;
        break;
    case 5:
        m_playerSee |= PLAYER_SIX_SEEN;
        break;
    case 6:
        m_playerSee |= PLAYER_SEVEN_SEEN;
        break;
    case 7:
        m_playerSee |= PLAYER_EIGHT_SEEN;
        break;
    default:
        assert(false && "Select a player from 0 to 7 to add vision to a tile.");
        break;
    }
}

void TileBase::PlayerDontSeeAnymore(int playerId)
{
    switch (playerId)
    {
    case 0:
        m_playerSee &= ~PLAYER_ONE_SEEN;
        break;
    case 1:
        m_playerSee &= ~PLAYER_TWO_SEEN;
        break;
    case 2:
        m_playerSee &= ~PLAYER_THREE_SEEN;
        break;
    case 3:
        m_playerSee &= ~PLAYER_FOUR_SEEN;
        break;
    case 4:
        m_playerSee &= ~PLAYER_FIVE_SEEN;
        break;
    case 5:
        m_playerSee &= ~PLAYER_SIX_SEEN;
        break;
    case 6:
        m_playerSee &= ~PLAYER_SEVEN_SEEN;
        break;
    case 7:
        m_playerSee &= ~PLAYER_EIGHT_SEEN;
        break;
    default:
        assert(false && "Select a player from 0 to 7 to know if a tile is not seen anymore.");
        break;
    }
}

bool TileBase::IsSeen(int playerId)
{
    bool isSeen = false;

    switch (playerId)
    {
    case 0:
        isSeen = (m_playerSee & PLAYER_ONE_SEEN) != 0;
        break;
    case 1:
        isSeen = (m_playerSee & PLAYER_TWO_SEEN) != 0;
        break;
    case 2:
        isSeen = (m_playerSee & PLAYER_THREE_SEEN) != 0;
        break;
    case 3:
        isSeen = (m_playerSee & PLAYER_FOUR_SEEN) != 0;
        break;
    case 4:
        isSeen = (m_playerSee & PLAYER_FIVE_SEEN) != 0;
        break;
    case 5:
        isSeen = (m_playerSee & PLAYER_SIX_SEEN) != 0;
        break;
    case 6:
        isSeen = (m_playerSee & PLAYER_SEVEN_SEEN) != 0;
        break;
    case 7:
        isSeen = (m_playerSee & PLAYER_EIGHT_SEEN) != 0;
        break;
    default:
        assert(false && "Select a player from 0 to 7 to know if a tile is seen.");
        break;
    }

    return isSeen;
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
    tileNode.put("<xmlattr>.D", m_playerDiscovered);

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