#include "UnitAxemanII.h"
#include <algorithm>
#include <iostream>
#include "GameSession.h"
#include "Player.h"

UnitAxemanII::UnitAxemanII(int owner, bool hasBonusActionPoint)
    : Unit<UnitAxemanII>(owner, HEALTH, ACTION_POINTS, ATTACK_RANGE, ATTACK_DAMAGE, VIEW_RANGE, UNIT_NAME, UNIT_TYPE, WEAPON_COST)
{
    if (hasBonusActionPoint)
    {
        m_actionPointsLeft += 1;
    }
}

UnitAxemanII::~UnitAxemanII()
{
}

std::shared_ptr<UnitBase> UnitAxemanII::Clone()
{
    return std::shared_ptr<UnitBase> { new UnitAxemanII{ *this } };
}

void UnitAxemanII::LoadTexture()
{
    try
    {
        m_Texture.LoadFromFile("..\\Sprite\\Units\\64x64\\axe2.bmp");
    }
    catch (std::exception e)
    {
        std::string msg{ e.what() };
        std::cout << msg << std::endl;
    }
}

bool UnitAxemanII::CanUpgrade()
{
    return false;
}

std::shared_ptr<UnitAxemanII> UnitAxemanII::Deserialize(boost::property_tree::ptree node)
{
    std::shared_ptr<UnitAxemanII> axeman = std::shared_ptr<UnitAxemanII>{ new UnitAxemanII(node.get<int>("<xmlattr>.O")) };
    axeman->m_health = node.get<int>("<xmlattr>.H");
    axeman->m_actionPointsLeft = node.get<int>("<xmlattr>.APL");

    return axeman;
}

AttackNotification UnitAxemanII::Attack(std::shared_ptr<UnitBase> target)
{
    UseActionPoints(m_actionPointsLeft);
    AttackNotification targetNotification = UnitBase::Attack(target);
    AttackNotification attackerNotification = ReceiveDamage(targetNotification.RiposteDamage);

    targetNotification.AttackerIsDead = attackerNotification.TargetIsDead;
    targetNotification.CanMove = true;

    return targetNotification;
}

AttackNotification UnitAxemanII::Attack(std::shared_ptr<DistrictBase> target)
{
    UseActionPoints(m_actionPointsLeft);
    AttackNotification targetNotification = UnitBase::Attack(target);
    AttackNotification attackerNotification = ReceiveDamage(targetNotification.RiposteDamage);

    targetNotification.AttackerIsDead = attackerNotification.TargetIsDead;
    targetNotification.CanMove = true;

    return targetNotification;
}