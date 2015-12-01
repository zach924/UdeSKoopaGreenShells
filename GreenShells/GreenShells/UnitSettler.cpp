#include "UnitSettler.h"
#include "GameSession.h"
#include "Player.h"
#include <iostream>

UnitSettler::UnitSettler(int owner, bool hasBonusActionPoint)
    : Unit<UnitSettler>(owner, HEALTH, ACTION_POINTS, MELEE_ATTACK_RANGE, ATTACK_DAMAGE, VIEW_RANGE, UNIT_NAME, UNIT_TYPE, WEAPON_COST, FOOD_COST, UPGRADE_TYPE)
{
    if (hasBonusActionPoint)
    {
        m_actionPointsLeft += 1;
    }
}

UnitSettler::~UnitSettler()
{
}

std::shared_ptr<UnitBase> UnitSettler::Clone()
{
    return std::shared_ptr<UnitBase> { new UnitSettler{ *this } };
}

void UnitSettler::LoadTexture()
{
    try
    {
        m_Texture.LoadFromFile("..\\Sprite\\Units\\64x64\\settler.bmp");
    }
    catch (std::exception e)
    {
        std::string msg{ e.what() };
        std::cout << msg << std::endl;
    }
}

bool UnitSettler::CanUpgrade()
{
    return true;
}

// NEED TO PUT THIS IN EVERY MELEE UNIT, SO THEY CAN REECEIVE DAMAGE WHEN ATTACKING
AttackNotification UnitSettler::Attack(std::shared_ptr<UnitBase> target)
{
    UseActionPoints(m_actionPointsLeft);
    AttackNotification targetNotification = UnitBase::Attack(target);
    AttackNotification attackerNotification = ReceiveDamage(targetNotification.RiposteDamage);

    targetNotification.AttackerIsDead = attackerNotification.TargetIsDead;
    targetNotification.CanMove = true;

    return targetNotification;
}

AttackNotification UnitSettler::Attack(std::shared_ptr<DistrictBase> target)
{
    UseActionPoints(m_actionPointsLeft);
    AttackNotification targetNotification = UnitBase::Attack(target);
    AttackNotification attackerNotification = ReceiveDamage(targetNotification.RiposteDamage);

    targetNotification.AttackerIsDead = attackerNotification.TargetIsDead;
    targetNotification.CanMove = true;

    return targetNotification;
}

std::shared_ptr<UnitSettler> UnitSettler::Deserialize(boost::property_tree::ptree node)
{
    std::shared_ptr<UnitSettler> settler = std::shared_ptr<UnitSettler>{ new UnitSettler(node.get<int>("<xmlattr>.O")) };
    settler->m_health = node.get<int>("<xmlattr>.H");
    settler->m_actionPointsLeft = node.get<int>("<xmlattr>.APL");

    return settler;
}