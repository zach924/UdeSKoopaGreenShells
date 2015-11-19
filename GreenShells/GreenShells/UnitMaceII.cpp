#include "UnitMaceII.h"
#include <algorithm>
#include <iostream>
#include "GameSession.h"
#include "Player.h"

const char* UnitMaceII::UNIT_NAME = "Mace MK2";

UnitMaceII::UnitMaceII(int owner)
    : Unit<UnitMaceII>(owner, HEALTH, MOVE_RANGE, ATTACK_RANGE, ATTACK_DAMAGE, VIEW_RANGE)
{
}

UnitMaceII::~UnitMaceII()
{
}

UnitBase* UnitMaceII::Clone()
{
    return new UnitMaceII{ *this };
}

void UnitMaceII::LoadTexture()
{
    try
    {
        m_Texture.LoadFromFile("..\\Sprite\\Units\\64x64\\mace2.bmp");
    }
    catch (std::exception e)
    {
        std::string msg{ e.what() };
        std::cout << msg << std::endl;
    }
}

bool UnitMaceII::CanUpgrade()
{
    return false;
}

int UnitMaceII::GetMaxHealth()
{
    return HEALTH;
}

const char * UnitMaceII::GetName()
{
    return UNIT_NAME;
}

int UnitMaceII::GetTypeAsInt()
{
    return UNIT_TYPE;
}

int UnitMaceII::GetViewRange()
{
    return VIEW_RANGE;
}

int UnitMaceII::GetUnitTier()
{
    return UNIT_TIER;
}

void UnitMaceII::Heal(int health)
{
    m_health = std::min(m_health + health, HEALTH);
}

UnitMaceII * UnitMaceII::Deserialize(boost::property_tree::ptree node)
{
    UnitMaceII* mace = new UnitMaceII(node.get<int>("<xmlattr>.O"));
    mace->m_health = node.get<int>("<xmlattr>.H");

    return mace;
}

AttackNotification UnitMaceII::Attack(UnitBase * target)
{
    AttackNotification targetNotification = UnitBase::Attack(target);
    AttackNotification attackerNotification = ReceiveDamage(targetNotification.RiposteDamage);

    targetNotification.AttackerIsDead = attackerNotification.TargetIsDead;
    targetNotification.CanMove = true;

    return targetNotification;
}

AttackNotification UnitMaceII::Attack(DistrictBase * target)
{
    AttackNotification targetNotification = UnitBase::Attack(target);
    AttackNotification attackerNotification = ReceiveDamage(targetNotification.RiposteDamage);

    targetNotification.AttackerIsDead = attackerNotification.TargetIsDead;
    targetNotification.CanMove = true;

    return targetNotification;
}
