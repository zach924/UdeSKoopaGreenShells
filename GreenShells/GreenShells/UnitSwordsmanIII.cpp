#include "UnitSwordsmanIII.h"
#include <iostream>
#include "GameSession.h"
#include "Player.h"

UnitSwordsmanIII::UnitSwordsmanIII(int owner, bool hasBonusActionPoint)
    : Unit<UnitSwordsmanIII>(owner, HEALTH, ACTION_POINTS, MELEE_ATTACK_RANGE, ATTACK_DAMAGE, VIEW_RANGE, UNIT_NAME, UNIT_TYPE, WEAPON_COST)
{
    if (hasBonusActionPoint)
    {
        m_actionPointsLeft += 1;
    }
}

UnitSwordsmanIII::~UnitSwordsmanIII()
{
}

std::shared_ptr<UnitBase> UnitSwordsmanIII::Clone()
{
    return std::shared_ptr<UnitBase> { new UnitSwordsmanIII{ *this } };
}

void UnitSwordsmanIII::LoadTexture()
{
    try
    {
        m_unitTexture.LoadFromFile("Ressources\\Sprite\\Units\\64x64\\sword3.bmp");
    }
    catch (std::exception e)
    {
        std::string msg{ e.what() };
        std::cout << msg << std::endl;
    }
}

bool UnitSwordsmanIII::CanUpgrade()
{
    return false;
}

// NEED TO PUT THIS IN EVERY MELEE UNIT, SO THEY CAN REECEIVE DAMAGE WHEN ATTACKING
AttackNotification UnitSwordsmanIII::Attack(std::shared_ptr<UnitBase> target)
{
    UseActionPoints(m_actionPointsLeft);
    AttackNotification targetNotification = UnitBase::Attack(target);
    AttackNotification attackerNotification = ReceiveDamage(targetNotification.RiposteDamage);

    targetNotification.AttackerIsDead = attackerNotification.TargetIsDead;
    targetNotification.CanMove = true;

    return targetNotification;
}

AttackNotification UnitSwordsmanIII::Attack(std::shared_ptr<DistrictBase> target)
{
    UseActionPoints(m_actionPointsLeft);
    AttackNotification targetNotification = UnitBase::Attack(target);
    AttackNotification attackerNotification = ReceiveDamage(targetNotification.RiposteDamage);

    targetNotification.AttackerIsDead = attackerNotification.TargetIsDead;
    targetNotification.CanMove = true;

    return targetNotification;
}

std::shared_ptr<UnitSwordsmanIII> UnitSwordsmanIII::Deserialize(boost::property_tree::ptree node)
{
    std::shared_ptr<UnitSwordsmanIII> swordsman = std::shared_ptr<UnitSwordsmanIII>{ new UnitSwordsmanIII(node.get<int>("<xmlattr>.O")) };
    swordsman->m_health = node.get<int>("<xmlattr>.H");
    swordsman->m_actionPointsLeft = node.get<int>("<xmlattr>.APL");

    return swordsman;
}


