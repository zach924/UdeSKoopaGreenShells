#include "UnitShield.h"
#include <algorithm>
#include <iostream>
#include "GameSession.h"
#include "Player.h"

UnitShield::UnitShield(int owner, bool hasBonusActionPoint)
    : Unit<UnitShield>(owner, HEALTH, ACTION_POINTS, ATTACK_RANGE, ATTACK_DAMAGE, VIEW_RANGE, UNIT_NAME, UNIT_TYPE, WEAPON_COST)
{
    if (hasBonusActionPoint)
    {
        m_actionPointsLeft += 1;
    }
}

UnitShield::~UnitShield()
{
}

std::shared_ptr<UnitBase> UnitShield::Clone()
{
    return std::shared_ptr<UnitBase> { new UnitShield{ *this } };
}

void UnitShield::LoadTexture()
{
    try
    {
        m_unitTexture.LoadFromFile("Ressources\\Sprite\\Units\\64x64\\shield.bmp");
    }
    catch (std::exception e)
    {
        std::string msg{ e.what() };
        std::cout << msg << std::endl;
    }
}

bool UnitShield::CanUpgrade()
{
    return false;
}

std::shared_ptr<UnitShield> UnitShield::Deserialize(boost::property_tree::ptree node)
{
    std::shared_ptr<UnitShield> shield = std::shared_ptr<UnitShield>{ new UnitShield(node.get<int>("<xmlattr>.O")) };
    shield->m_health = node.get<int>("<xmlattr>.H");
    shield->m_actionPointsLeft = node.get<int>("<xmlattr>.APL");

    return shield;
}

AttackNotification UnitShield::Attack(std::shared_ptr<UnitBase> target)
{
    UseActionPoints(m_actionPointsLeft);
    AttackNotification targetNotification = UnitBase::Attack(target);
    AttackNotification attackerNotification = ReceiveDamage(targetNotification.RiposteDamage);

    targetNotification.AttackerIsDead = attackerNotification.TargetIsDead;
    targetNotification.CanMove = true;

    return targetNotification;
}

AttackNotification UnitShield::Attack(std::shared_ptr<DistrictBase> target)
{
    UseActionPoints(m_actionPointsLeft);
    AttackNotification targetNotification = UnitBase::Attack(target);
    AttackNotification attackerNotification = ReceiveDamage(targetNotification.RiposteDamage);

    targetNotification.AttackerIsDead = attackerNotification.TargetIsDead;
    targetNotification.CanMove = true;

    return targetNotification;
}