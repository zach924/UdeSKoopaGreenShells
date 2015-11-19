#include "UnitAxemanII.h"
#include <algorithm>
#include <iostream>
#include "GameSession.h"
#include "Player.h"

const char* UnitAxemanII::UNIT_NAME = "Axeman MK2";

UnitAxemanII::UnitAxemanII(int owner)
    : Unit<UnitAxemanII>(owner, HEALTH, MOVE_RANGE, ATTACK_RANGE, ATTACK_DAMAGE, VIEW_RANGE)
{
}

UnitAxemanII::~UnitAxemanII()
{
}

UnitBase* UnitAxemanII::Clone()
{
    return new UnitAxemanII{ *this };
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

int UnitAxemanII::GetMaxHealth()
{
    return HEALTH;
}

const char * UnitAxemanII::GetName()
{
    return UNIT_NAME;
}

int UnitAxemanII::GetTypeAsInt()
{
    return UNIT_TYPE;
}

int UnitAxemanII::GetViewRange()
{
    return VIEW_RANGE;
}

int UnitAxemanII::GetUnitTier()
{
    return UNIT_TIER;
}

void UnitAxemanII::Heal(int health)
{
    m_health = std::min(m_health + health, HEALTH);
}

UnitAxemanII * UnitAxemanII::Deserialize(boost::property_tree::ptree node)
{
    UnitAxemanII* axeman = new UnitAxemanII(node.get<int>("<xmlattr>.O"));
    axeman->m_health = node.get<int>("<xmlattr>.H");

    return axeman;
}

AttackNotification UnitAxemanII::Attack(UnitBase * target)
{
    AttackNotification targetNotification = UnitBase::Attack(target);
    AttackNotification attackerNotification = ReceiveDamage(targetNotification.RiposteDamage);

    targetNotification.AttackerIsDead = attackerNotification.TargetIsDead;
    targetNotification.CanMove = true;

    return targetNotification;
}

AttackNotification UnitAxemanII::Attack(DistrictBase * target)
{
    AttackNotification targetNotification = UnitBase::Attack(target);
    AttackNotification attackerNotification = ReceiveDamage(targetNotification.RiposteDamage);

    targetNotification.AttackerIsDead = attackerNotification.TargetIsDead;
    targetNotification.CanMove = true;

    return targetNotification;
}