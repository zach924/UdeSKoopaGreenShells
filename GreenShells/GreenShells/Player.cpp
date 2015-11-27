#include "Player.h"
#include "GameSession.h"
#include <boost\property_tree\ptree.hpp>
#include "UnitSettler.h"
#include "UnitBuilder.h"

#include "UnitSwordsmanI.h"
#include "UnitSwordsmanII.h"
#include "UnitSwordsmanIII.h"

#include "UnitArcherI.h"
#include "UnitArcherII.h"
#include "UnitArcherIII.h"

#include "UnitAxemanI.h"
#include "UnitAxemanII.h"

#include "UnitMaceI.h"
#include "UnitMaceII.h"

#include "UnitCannon.h"
#include "UnitShield.h"

#include "Map.h"

#include "DistrictCityCenter.h"

#include "DistrictHunter.h"
#include "DistrictFarm.h"
#include "DistrictWindMill.h"

#include "DistrictBlacksmith.h"
#include "DistrictStable.h"
#include "DistrictFort.h"

#include "DistrictMonastery.h"
#include "DistrictCathedral.h"
#include "DistrictSchool.h"

#include "DistrictInn.h"
#include "DistrictTavern.h"
#include "DistrictMilitaryTent.h"
const double Player::BORDER_GROWTH_BONUS_RATE = 0.85f;
Player::Player()
    :m_playerID(),
    m_playerName(),
    m_isReadyForNewTurn(false),
    m_isAlive(true),
    m_cityCenterLocations(),
    m_unitCount(0),
    m_food(200),
    m_science(0),
    m_weapon(0),
    m_foodMultiplier(1),
    m_scienceMultiplier(1),
    m_weaponMultiplier(1),
    m_isDisconnected(false),
    m_armySkillTree(),
    m_empireSkillTree(),
    m_utilitySkillTree(),
    m_diplomaticRelations()
{
}

Player::~Player()
{
}

std::string Player::GetPlayerName()
{
    return m_playerName;
}

int Player::GetPlayerID()
{
    return m_playerID;
}

bool Player::IsPlayerReadyForNextTurn()
{
    return m_isDisconnected || m_isReadyForNewTurn;
}

int Player::GetFood()
{
    return m_food;
}

int Player::GetScience()
{
    return m_science;
}

int Player::GetWeapon()
{
    return m_weapon;
}

bool Player::IsAlive()
{
    return m_isAlive;
}

bool Player::IsNegociating()
{
    for (auto relation : m_diplomaticRelations)
    {
        if (relation.second.GetRelationStatus() == RelationStatus::NegocatingAlliance || relation.second.GetRelationStatus() == RelationStatus::NegociatingPeace)
        {
            return true;
        }
    }
    return false;
}

std::set<Position> Player::GetCityCenterTilesOwned(int currentTurn, Map* map, Position cityCenterPos)
{
    std::map<Position, int> ownedTiles;
    auto cityCenterTier = currentTurn - m_cityCenterLocations[cityCenterPos];
    if (cityCenterTier > DistrictCityCenter::TURN_FOR_BORDER_T4)
    {
        ownedTiles = map->GetArea(cityCenterPos, DistrictCityCenter::T4_BORDER_SIZE, NO_FILTER);
    }
    else if (cityCenterTier > DistrictCityCenter::TURN_FOR_BORDER_T3)
    {
        ownedTiles = map->GetArea(cityCenterPos, DistrictCityCenter::T3_BORDER_SIZE, NO_FILTER);
    }
    else if (cityCenterTier > DistrictCityCenter::TURN_FOR_BORDER_T2)
    {
        ownedTiles = map->GetArea(cityCenterPos, DistrictCityCenter::T2_BORDER_SIZE, NO_FILTER);
    }
    else if (cityCenterTier > DistrictCityCenter::TURN_FOR_BORDER_T1)
    {
        ownedTiles = map->GetArea(cityCenterPos, DistrictCityCenter::T1_BORDER_SIZE, NO_FILTER);
    }
    else
    {
        ownedTiles = map->GetArea(cityCenterPos, 0, NO_FILTER);
    }

    std::set<Position> result;
    for (const std::pair<Position, int>& pos : ownedTiles)
    {
        result.emplace(pos.first);
    }

    return result;
}

bool Player::IsDisconnected()
{
    return m_isDisconnected;
}

boost::property_tree::ptree Player::Serialize()
{
    boost::property_tree::ptree playerNode;
    playerNode.put("<xmlattr>.PId", m_playerID);
    playerNode.put("<xmlattr>.PName", m_playerName);
    playerNode.put("<xmlattr>.UC", m_unitCount);
    playerNode.put("<xmlattr>.F", m_food);
    playerNode.put("<xmlattr>.S", m_science);
    playerNode.put("<xmlattr>.W", m_weapon);
    playerNode.put("<xmlattr>.FM", m_foodMultiplier);
    playerNode.put("<xmlattr>.SM", m_scienceMultiplier);
    playerNode.put("<xmlattr>.WM", m_weaponMultiplier);
    playerNode.put("<xmlattr>.IA", m_isAlive);
    playerNode.put("<xmlattr>.IR", m_isReadyForNewTurn);
    playerNode.put("<xmlattr>.ID", m_isDisconnected);
    playerNode.put("<xmlattr>.UST", m_utilitySkillTree.toString());
    playerNode.put("<xmlattr>.EST", m_empireSkillTree.toString());
    playerNode.put("<xmlattr>.AST", m_armySkillTree.toString());

    boost::property_tree::ptree& diplomaticRelationsNode = playerNode.add("DR", "");
    for (auto relation = m_diplomaticRelations.begin(); relation != m_diplomaticRelations.end(); ++relation)
    {
        boost::property_tree::ptree& relationNode = diplomaticRelationsNode.add("R", "");
        relationNode.put("<xmlattr>.SP", relation->first);//SP = Second Player
        relationNode.put("<xmlattr>.RS", relation->second.GetRelationStatus());//RS = Relation Status
        relationNode.put("<xmlattr>.MA", relation->second.GetMustAnswerPlayerId());//MA = Must Answer Player Id
        relationNode.put("<xmlattr>.PT", relation->second.GetPropositionTurn());//PT = Proposition Turn
    }

    boost::property_tree::ptree& cityCenterListNode = playerNode.add("CCL", "");
    for (auto cityCenter : m_cityCenterLocations)
    {
        boost::property_tree::ptree cityCenterNode;
        cityCenterNode.put("<xmlattr>.Co", cityCenter.first.Column);
        cityCenterNode.put("<xmlattr>.Ro", cityCenter.first.Row);
        cityCenterNode.put("<xmlattr>.TF", cityCenter.second);
        cityCenterListNode.add_child("CC", cityCenterNode);
    }
    return playerNode;
}

std::map<Position, int> Player::GetCityCenterLocations()
{
    return m_cityCenterLocations;
}

std::map<int, DiplomaticRelation> Player::GetDiplomaticRelations()
{
    return m_diplomaticRelations;
}

MapFilter Player::GetMoveRestriction()
{
    MapFilter moveRestriction = ALLOW_GROUND | BLOCK_ENEMIES;
    if (m_utilitySkillTree.Embark)
    {
        moveRestriction |= ALLOW_WATER;
    }

    if (m_utilitySkillTree.MountainWalking)
    {
        moveRestriction |= ALLOW_MOUNTAIN;
    }
    return moveRestriction;
}

UtilitySkillTree Player::GetUtilitySkillTree()
{
    return m_utilitySkillTree;
}
ArmySkillTree Player::GetArmySkillTree()
{
    return m_armySkillTree;
}
EmpireSkillTree Player::GetEmpireSkillTree()
{
    return m_empireSkillTree;
}

bool Player::HasRessourcesForUnit(int tier)
{
    if (tier == 1)
    {
        return m_weapon >= UNIT_TIER_ONE_COST;
    }
    else if (tier == 2)
    {
        return m_weapon >= UNIT_TIER_TWO_COST;

    }
    else if (tier == 3)
    {
        return m_weapon >= UNIT_TIER_THREE_COST;

    }
    else if (tier == 4)
    {
        return m_weapon >= UNIT_TIER_FOUR_COST;
    }
    return false;
}

bool Player::HasRessourcesForDistrict(int DistrictType)
{
    switch (DistrictType)
    {
    case DistrictCityCenter::DISTRICT_TYPE:
        return m_food >= CITY_CENTER_COST;
        break;
    case DistrictHunter::DISTRICT_TYPE:
        return m_food >= HUNTER_COST;
        break;
    case DistrictFarm::DISTRICT_TYPE:
        return m_food >= FARM_COST;
        break;
    case DistrictWindMill::DISTRICT_TYPE:
        return m_food >= WIND_MILL_COST;
        break;
    case DistrictBlacksmith::DISTRICT_TYPE:
        return m_food >= BLACKSMITH_COST;
        break;
    case DistrictStable::DISTRICT_TYPE:
        return m_food >= STABLE_COST;
        break;
    case DistrictFort::DISTRICT_TYPE:
        return m_food >= FORT_COST;
        break;
    case DistrictMonastery::DISTRICT_TYPE:
        return m_food >= MONASTERY_COST;
        break;
    case DistrictCathedral::DISTRICT_TYPE:
        return m_food >= CATHEDRAL_COST;
        break;
    case DistrictSchool::DISTRICT_TYPE:
        return m_food >= SCHOOL_COST;
        break;
    case DistrictInn::DISTRICT_TYPE:
        return m_food >= INN_COST;
        break;
    case DistrictTavern::DISTRICT_TYPE:
        return m_food >= TAVERN_COST;
        break;
    default:
        return false;
        break;
    }

}

unsigned int Player::GetWeaponCostForTier(int tier)
{
    if (tier == 1)
    {
        return UNIT_TIER_ONE_COST;
    }
    else if (tier == 2)
    {
        return UNIT_TIER_TWO_COST;

    }
    else if (tier == 3)
    {
        return UNIT_TIER_THREE_COST;

    }
    else if (tier == 4)
    {
        return UNIT_TIER_FOUR_COST;
    }
    return 0;
}

unsigned int Player::GetDistrictCost(int districtType)
{
    switch (districtType)
    {
    case DistrictCityCenter::DISTRICT_TYPE:
        return CITY_CENTER_COST;
        break;
    case DistrictHunter::DISTRICT_TYPE:
        return HUNTER_COST;
        break;
    case DistrictFarm::DISTRICT_TYPE:
        return FARM_COST;
        break;
    case DistrictWindMill::DISTRICT_TYPE:
        return WIND_MILL_COST;
        break;
    case DistrictBlacksmith::DISTRICT_TYPE:
        return BLACKSMITH_COST;
        break;
    case DistrictStable::DISTRICT_TYPE:
        return STABLE_COST;
        break;
    case DistrictFort::DISTRICT_TYPE:
        return FORT_COST;
        break;
    case DistrictMonastery::DISTRICT_TYPE:
        return MONASTERY_COST;
        break;
    case DistrictCathedral::DISTRICT_TYPE:
        return CATHEDRAL_COST;
        break;
    case DistrictSchool::DISTRICT_TYPE:
        return SCHOOL_COST;
        break;
    case DistrictInn::DISTRICT_TYPE:
        return INN_COST;
        break;
    case DistrictTavern::DISTRICT_TYPE:
        return TAVERN_COST;
        break;
    default:
        return false;
        break;
    }
}

int Player::GetSwordsmanTier()
{
    if (m_armySkillTree.SwordT3)
    {
        return UnitSwordsmanIII::UNIT_TIER;
    }
    else if (m_armySkillTree.SwordT2)
    {
        return UnitSwordsmanII::UNIT_TIER;
    }
    else
    {
        return UnitSwordsmanI::UNIT_TIER;
    }
}

int Player::GetArcherTier()
{
    if (m_armySkillTree.RangerT3)
    {
        return UnitArcherIII::UNIT_TIER;
    }
    else if (m_armySkillTree.RangerT2)
    {
        return UnitArcherII::UNIT_TIER;
    }
    else if (m_armySkillTree.RangerT1)
    {
        return UnitArcherI::UNIT_TIER;
    }
    else
    {
        return -1;
    }
}

int Player::GetAxemanTier()
{
    if (m_armySkillTree.AxeT2)
    {
        return UnitAxemanII::UNIT_TIER;
    }
    else if (m_armySkillTree.AxeT1)
    {
        return UnitAxemanI::UNIT_TIER;
    }
    else
    {
        return -1;
    }
}

int Player::GetMaceTier()
{
    if (m_armySkillTree.MaceT2)
    {
        return UnitMaceII::UNIT_TIER;
    }
    else if (m_armySkillTree.MaceT1)
    {
        return UnitMaceI::UNIT_TIER;
    }
    else
    {
        return -1;
    }
}

int Player::GetCannonTier()
{
    if (m_armySkillTree.Canon)
    {
        return UnitCannon::UNIT_TIER;
    }
    else
    {
        return -1;
    }


}

int Player::GetShieldTier()
{
    if (m_armySkillTree.Shield)
    {
        return UnitShield::UNIT_TIER;
    }
    else
    {
        return -1;
    }
}

int Player::GetSettlerTier()
{
    if (m_empireSkillTree.Settler)
    {
        return UnitSettler::UNIT_TIER;
    }
    else
    {
        return -1;
    }
}

int Player::GetBuilderTier()
{
    if (m_utilitySkillTree.Watchtower)
    {
        return UnitBuilder::UNIT_TIER;
    }
    else
    {
        return -1;
    }
}
