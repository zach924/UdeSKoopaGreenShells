#include "Player.h"
#include "GameSession.h"
#include <boost\property_tree\ptree.hpp>


Player::Player()
    :m_playerID(),
    m_playerName(),
    m_isReadyForNewTurn(false),
    m_isAlive(true),
    m_cityCenterLocations(),
    m_unitCount(0),
    m_food(100),
    m_science(0),
    m_weapon(0),
    m_foodMultiplier(1),
    m_scienceMultiplier(1),
    m_weaponMultiplier(1),
    m_isDisconnected(false),
    m_armySkillTree(),
    m_empireSkillTree(),
    m_utilitySkillTree()
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

