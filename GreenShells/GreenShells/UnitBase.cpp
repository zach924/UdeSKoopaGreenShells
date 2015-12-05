#include <iostream>
#include <algorithm>
#include <boost\property_tree\ptree.hpp>
#include "UnitBase.h"
#include "DistrictBase.h"
#include "ServerSession.h"
#include "Player.h"

UnitBase::UnitBase(int owner, int health, int actionPoints, int attackRange, int attackDamage, int viewRange, const char* name, int typeAsInt, int weaponCost, int foodCost, int upgradeType)
    : m_ownerID(owner),
    m_health(health),
    m_maxHealth(health),
    m_attackRange(attackRange),
    m_attackDamage(attackDamage),
    m_actionPointsLeft(actionPoints),
    m_defaultActionPoints(actionPoints),
    m_viewRange(viewRange),
    m_name(name),
    m_typeAsInt(typeAsInt),
    m_weaponCost(weaponCost),
    m_foodCost(foodCost),
    m_upgradeType(upgradeType)
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

int UnitBase::GetUpgradeType()
{
    return m_upgradeType;
}

int UnitBase::GetMaxHealth()
{
    return m_maxHealth;
}

const char * UnitBase::GetName()
{
    return m_name.c_str();
}

int UnitBase::GetTypeAsInt()
{
    return m_typeAsInt;
}

int UnitBase::GetViewRange()
{
    return m_viewRange;
}

Position UnitBase::GetPosition()
{
    return m_position;
}

void UnitBase::SetPosition(Position pos)
{
    m_position = pos;
}

void UnitBase::Heal(int health)
{
    UseActionPoints(m_actionPointsLeft);
    m_health = std::min(m_health + health, m_maxHealth);
}

int UnitBase::GetWeaponCost()
{
    assert(m_weaponCost >= 0 && "You must set a weaponCost to your unit");
    return m_weaponCost;
}

int UnitBase::GetFoodCost()
{
    assert(m_weaponCost >= 0 && "You are trying to get the food cost of a unit but didn't set any.");
    return m_foodCost;
}

AttackNotification UnitBase::ReceiveDamage(int damage)
{
    if (ServerSession::GetInstance().GetWorldState()->GetPlayerCopy(m_ownerID)->GetUtilitySkillTree().ArmorUpgrade)
    {
        damage = static_cast<int>(damage * 0.85);
    }
    m_health -= damage;

    return AttackNotification{ GetAttackDamage() / 2, (m_health <= 0), false };
}

AttackNotification UnitBase::Attack(std::shared_ptr<UnitBase> target)
{
    UseActionPoints(m_actionPointsLeft);
    AttackNotification targetNotification = target->ReceiveDamage(GetAttackDamage()  * ServerSession::GetInstance().GetWorldState()->GetPlayerCopy(m_ownerID)->GetAttackMultiplier());

    return targetNotification;
}

AttackNotification UnitBase::Attack(std::shared_ptr<DistrictBase> target)
{
    UseActionPoints(m_actionPointsLeft);
    AttackNotification targetNotification = target->ReceiveDamage(GetAttackDamage());

    return targetNotification;
}

void UnitBase::NotifyNewTurn(int turn)
{
    m_actionPointsLeft = m_defaultActionPoints;
    auto player = ServerSession::GetInstance().GetWorldState()->GetPlayerCopy(m_ownerID);
    if (player->GetUtilitySkillTree().MovementUpgrade)
    {
        m_actionPointsLeft += 1;
    }
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