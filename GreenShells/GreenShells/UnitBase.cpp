#include <iostream>
#include <algorithm>
#include <boost\property_tree\ptree.hpp>
#include "UnitBase.h"
#include "DistrictBase.h"
#include "ServerSession.h"
#include "Player.h"

UnitBase::UnitBase(int owner, int health, int actionPoints, int attackRange, int attackDamage, int viewRange)
    : m_ownerID(owner),
    m_health(health),
    m_foodCost(0),
    m_scienceCost(0),
    m_weaponCost(0),
    m_attackRange(attackRange),
    m_attackDamage(attackDamage),
    m_actionPointsLeft(actionPoints),
    m_viewRange(viewRange)
{
}

UnitBase::~UnitBase()
{
}

void UnitBase::UseActionPoints(int points)
{
    m_actionPointsLeft = std::max(0, m_actionPointsLeft - points);
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
    if (ServerSession::GetInstance().GetWorldState()->GetPlayerCopy(m_ownerID)->GetUtilitySkillTree().ArmorUpgrade)
    {
        damage = static_cast<int>(damage * 0.85);
    }
    m_health -= damage;

    return AttackNotification{ m_attackDamage / 2, (m_health <= 0), false };
}

AttackNotification UnitBase::Attack(std::shared_ptr<UnitBase> target)
{
    UseActionPoints(10);
    AttackNotification targetNotification = target->ReceiveDamage(GetAttackDamage());

    return targetNotification;
}

AttackNotification UnitBase::Attack(std::shared_ptr<DistrictBase> target)
{
    UseActionPoints(10);
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
    unitNode.put("<xmlattr>.APL", m_actionPointsLeft);

    return unitNode;
}