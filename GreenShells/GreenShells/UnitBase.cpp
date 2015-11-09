#include <iostream>
#include <algorithm>
#include <boost\property_tree\ptree.hpp>
#include "UnitBase.h"
#include "DistrictBase.h"

UnitBase::UnitBase(int owner, int health, int moveRange, int attackRange, int attackDamage)
    : m_ownerID(owner),
    m_health(health),
    m_foodCost(0),
    m_scienceCost(0),
    m_weaponCost(0),
    m_moveRange(moveRange),
    m_attackRange(attackRange),
    m_attackDamage(attackDamage),
    m_actionPointsLeft(1)
{
}

UnitBase::~UnitBase()
{
}

int UnitBase::GetActionPointsRemaining()
{
    return m_actionPointsLeft;
}

int UnitBase::GetAttackDamage()
{
    return m_attackDamage;
}

int UnitBase::GetAttackRange()
{
    return m_attackRange;
}

int UnitBase::GetHealth()
{
    return m_health;
}

int UnitBase::GetMoveRange()
{
    return m_moveRange;
}

int UnitBase::GetOwnerID()
{
    return m_ownerID;
}

Position UnitBase::GetPosition()
{
    return m_position;
}

void UnitBase::SetPosition(Position pos)
{
    m_position = pos;
}

AttackNotification UnitBase::ReceiveDamage(int damage)
{
    m_health -= damage;

    if (m_health <= 0)
        std::cout << "An unit die : Player " << m_ownerID << std::endl;

    return AttackNotification{ m_attackDamage / 2, (m_health <= 0), false };
}

AttackNotification UnitBase::Attack(UnitBase * target)
{
    AttackNotification targetNotification = target->ReceiveDamage(GetAttackDamage());

    return targetNotification;
}

AttackNotification UnitBase::Attack(DistrictBase * target)
{
    AttackNotification targetNotification = target->ReceiveDamage(GetAttackDamage());

    return targetNotification;
}

void UnitBase::NotifyNewTurn(int turn)
{
}

boost::property_tree::ptree UnitBase::Serialize()
{
    boost::property_tree::ptree unitNode;
    unitNode.put("<xmlattr>.T", GetTypeAsInt());
    unitNode.put("<xmlattr>.O", m_ownerID);
    unitNode.put("<xmlattr>.H", m_health);

    return unitNode;
}