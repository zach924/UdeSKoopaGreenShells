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
    m_food(120),
    m_science(0),
    m_weapon(0),
    m_foodPerTurn(0),
    m_sciencePerTurn(0),
    m_weaponPerTurn(0),
    m_foodMultiplier(1),
    m_scienceMultiplier(1),
    m_weaponMultiplier(1),
    m_attackMultiplier(1),
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

int Player::GetPrintableFoodQuantity()
{
    return static_cast<int>(m_food);
}

int Player::GetPrintableScienceQuantity()
{
    return static_cast<int>(m_science);
}

int Player::GetPrintableWeaponQuantity()
{
    return static_cast<int>(m_weapon);
}

int Player::GetPrintableFoodPerTurn()
{
    return static_cast<int>(m_foodPerTurn);
}

int Player::GetPrintableSciencePerTurn()
{
    return static_cast<int>(m_sciencePerTurn);
}

int Player::GetPrintableWeaponPerTurn()
{
    return static_cast<int>(m_weaponPerTurn);
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
        ownedTiles = map->GetArea(cityCenterPos, DistrictCityCenter::T4_BORDER_SIZE, NO_FILTER, false);
    }
    else if (cityCenterTier > DistrictCityCenter::TURN_FOR_BORDER_T3)
    {
        ownedTiles = map->GetArea(cityCenterPos, DistrictCityCenter::T3_BORDER_SIZE, NO_FILTER, false);
    }
    else if (cityCenterTier > DistrictCityCenter::TURN_FOR_BORDER_T2)
    {
        ownedTiles = map->GetArea(cityCenterPos, DistrictCityCenter::T2_BORDER_SIZE, NO_FILTER, false);
    }
    else if (cityCenterTier > DistrictCityCenter::TURN_FOR_BORDER_T1)
    {
        ownedTiles = map->GetArea(cityCenterPos, DistrictCityCenter::T1_BORDER_SIZE, NO_FILTER, false);
    }
    else
    {
        ownedTiles = map->GetArea(cityCenterPos, 0, NO_FILTER, false);
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
    playerNode.put("<xmlattr>.FP", m_foodPerTurn);
    playerNode.put("<xmlattr>.SP", m_sciencePerTurn);
    playerNode.put("<xmlattr>.WP", m_weaponPerTurn);
    playerNode.put("<xmlattr>.FM", m_foodMultiplier);
    playerNode.put("<xmlattr>.SM", m_scienceMultiplier);
    playerNode.put("<xmlattr>.WM", m_weaponMultiplier);
    playerNode.put("<xmlattr>.AM", m_attackMultiplier);
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

boost::property_tree::ptree Player::SerializeOnlyPlayer()
{
    boost::property_tree::ptree playerXml;

    boost::property_tree::ptree& playerNode = playerXml.add("P", "");
    playerNode.put("<xmlattr>.PId", m_playerID);
    playerNode.put("<xmlattr>.PName", m_playerName);
    playerNode.put("<xmlattr>.UC", m_unitCount);
    playerNode.put("<xmlattr>.F", m_food);
    playerNode.put("<xmlattr>.S", m_science);
    playerNode.put("<xmlattr>.W", m_weapon);
    playerNode.put("<xmlattr>.FP", m_foodPerTurn);
    playerNode.put("<xmlattr>.SP", m_sciencePerTurn);
    playerNode.put("<xmlattr>.WP", m_weaponPerTurn);
    playerNode.put("<xmlattr>.FM", m_foodMultiplier);
    playerNode.put("<xmlattr>.SM", m_scienceMultiplier);
    playerNode.put("<xmlattr>.WM", m_weaponMultiplier);
    playerNode.put("<xmlattr>.AM", m_attackMultiplier);
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
    return playerXml;
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

double Player::GetAttackMultiplier()
{
    return m_attackMultiplier;
}

bool Player::HasEnoughWeapons(unsigned int WeaponCost)
{
    return m_weapon >= WeaponCost;
}

bool Player::HasEnoughFood(unsigned int FoodCost)
{
    return m_food >= FoodCost;
}