#include "UnitSettler.h"
#include <iostream>

UnitSettler::UnitSettler(int owner)
    : Unit<UnitSettler>(owner, HEALTH, MOVE_RANGE, MELEE_ATTACK_RANGE, ATTACK_DAMAGE)
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
		std::cout << "Loading UNIT_SETTLER" << std::endl;
	}
    catch (std::exception e)
    {
        std::string msg{ e.what() };
        std::cout << msg << std::endl;
    }
}

int UnitSettler::GetTypeAsInt()
{
    return UNIT_TYPE;
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