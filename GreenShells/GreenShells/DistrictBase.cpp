#include "DistrictBase.h"
#include <iostream>
#include <boost\property_tree\ptree.hpp>

DistrictBase::DistrictBase(int owner, int health, int attackDamage, int foodCost, int foodBonus, int scienceBonus, int weaponBonus)
    : m_ownerID(owner),
    m_health(health),
    m_attackDamage(attackDamage),
    m_foodCost(foodCost),
    m_scienceBonus(scienceBonus),
    m_weaponBonus(weaponBonus),
    m_actionPointsLeft(1)
{
}

DistrictBase::~DistrictBase()
{
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

AttackNotification DistrictBase::ReceiveDamage(int damage)
{
    m_health = std::max(m_health - damage, 0);

    if (m_health <= 0)
        std::cout << "A district got destroy : Player " << m_ownerID << std::endl;

    return AttackNotification{ m_attackDamage / 2, (m_health <= 0), false };
}

void DistrictBase::NotifyNewTurn(int turn)
{
}

boost::property_tree::ptree DistrictBase::Serialize()
{
    boost::property_tree::ptree districtNode;
    districtNode.put("<xmlattr>.T", GetTypeAsInt());
    districtNode.put("<xmlattr>.O", m_ownerID);
    districtNode.put("<xmlattr>.H", m_health);

    return districtNode;
}