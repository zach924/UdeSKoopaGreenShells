#include "UnitSettler.h"
#include <iostream>

const char* UnitSettler::UNIT_NAME = "Settler";

UnitSettler::UnitSettler(int owner)
    : Unit<UnitSettler>(owner, HEALTH, MOVE_RANGE, MELEE_ATTACK_RANGE, ATTACK_DAMAGE, VIEW_RANGE)
{
}

UnitSettler::~UnitSettler()
{
}

UnitBase* UnitSettler::Clone()
{
    return new UnitSettler{ *this };
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
    return true; // TODO :  Validate if its true by default for settler
}

int UnitSettler::GetMaxHealth()
{
    return HEALTH;
}

const char * UnitSettler::GetName()
{
    return UNIT_NAME;
}

int UnitSettler::GetTypeAsInt()
{
    return UNIT_TYPE;
}

int UnitSettler::GetViewRange()
{
    return VIEW_RANGE;
}

int UnitSettler::GetUnitTier()
{
    return UNIT_TIER;
}

void UnitSettler::Heal(int health)
{
    m_health = std::min(m_health + health, HEALTH);
}

// NEED TO PUT THIS IN EVERY MELEE UNIT, SO THEY CAN REECEIVE DAMAGE WHEN ATTACKING
AttackNotification UnitSettler::Attack(UnitBase * target)
{
    AttackNotification targetNotification = UnitBase::Attack(target);
    AttackNotification attackerNotification = ReceiveDamage(targetNotification.RiposteDamage);

    targetNotification.AttackerIsDead = attackerNotification.TargetIsDead;
    targetNotification.CanMove = true;

    return targetNotification;
}

AttackNotification UnitSettler::Attack(DistrictBase * target)
{
    AttackNotification targetNotification = UnitBase::Attack(target);
    AttackNotification attackerNotification = ReceiveDamage(targetNotification.RiposteDamage);

    targetNotification.AttackerIsDead = attackerNotification.TargetIsDead;
    targetNotification.CanMove = true;

    return targetNotification;
}

UnitSettler * UnitSettler::Deserialize(boost::property_tree::ptree node)
{
    UnitSettler* settler = new UnitSettler(node.get<int>("<xmlattr>.O"));
    settler->m_health = node.get<int>("<xmlattr>.H");

    return settler;
}