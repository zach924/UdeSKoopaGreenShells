#include "DistrictBase.h"
#include <iostream>
#include "ServerSession.h"
#include "Player.h"
#include "Map.h"
#include <boost\property_tree\ptree.hpp>

DistrictBase::DistrictBase(int owner, int health, int attackDamage, int viewRange, const char* name, int typeAsInt, int foodCost, int weaponYield, int foodYield, int scienceYield, int upgradeType)
    : m_ownerID(owner),
    m_maxHealth(health),
    m_health(health),
    m_name(name),
    m_typeAsInt(typeAsInt),
    m_attackDamage(attackDamage),
    m_weaponYield(weaponYield),
    m_foodYield(foodYield),
    m_scienceYield(scienceYield),
    m_foodCost(foodCost),
    m_actionPointsLeft(1),
    m_viewRange(viewRange),
    m_upgradeType(upgradeType)
{
}

DistrictBase::~DistrictBase()
{
}

void DistrictBase::ChangeOwner(int newOwner)
{
    m_ownerID = newOwner;
}

int DistrictBase::GetFoodCost()
{
    return m_foodCost;
}

int DistrictBase::GetActionPointsRemaining()
{
    return m_actionPointsLeft;
}

int DistrictBase::GetAttackDamage()
{
    return m_attackDamage;
}

int DistrictBase::GetHealth()
{
    return m_health;
}

int DistrictBase::GetOwnerID()
{
    return m_ownerID;
}

Position DistrictBase::GetPosition()
{
    return m_position;
}

void DistrictBase::SetPosition(Position pos)
{
    m_position = pos;
}

int DistrictBase::GetMaxHealth()
{
    return m_maxHealth;
}

int DistrictBase::GetUpgradeType()
{
    return m_upgradeType;
}

const char * DistrictBase::GetName()
{
    return m_name.c_str();
}

int DistrictBase::GetTypeAsInt()
{
    return m_typeAsInt;
}

int DistrictBase::GetViewRange()
{
    return m_viewRange;
}

void DistrictBase::Repair(int repairValue)
{
    m_health = std::min(m_health + repairValue, m_maxHealth);
}

AttackNotification DistrictBase::ReceiveDamage(int damage)
{
    m_health = std::max(m_health - damage, 0);

    if (m_health <= 0)
        std::cout << "A district got destroy : Player " << m_ownerID << std::endl;

    return AttackNotification{ m_attackDamage / 2, (m_health <= 0), false };
}

void DistrictBase::NotifyNewTurn(int turn)
{
    auto player = ServerSession::GetInstance().GetWorldState()->GetPlayer(GetOwnerID());
    player->AddWeapon(m_weaponYield);
    player->AddFood(m_foodYield);
    player->AddScience(m_scienceYield);
}

boost::property_tree::ptree DistrictBase::Serialize()
{
    boost::property_tree::ptree districtNode;
    districtNode.put("<xmlattr>.T", GetTypeAsInt());
    districtNode.put("<xmlattr>.O", m_ownerID);
    districtNode.put("<xmlattr>.H", m_health);

    return districtNode;
}