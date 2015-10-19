#include "Swordsman.h"
#include <iostream>

Swordsman::Swordsman(int owner)
	: Unit<Swordsman>(owner, HEALTH, MELEE_ATTACK_RANGE, ATTACK_DAMAGE)
{
}

Swordsman::~Swordsman()
{
}

void Swordsman::LoadTexture()
{
	try
	{
		m_Texture.LoadFromFile("..\\Sprite\\Units\\64x64\\Sword.bmp", nullptr);
	}
	catch (std::exception e)
	{
		std::string msg{ e.what() };
		std::cout << msg << std::endl;
	}
}

void Swordsman::Heal(int health)
{
	m_health = std::min(m_health + health, HEALTH);
}

// NEED TO PUT THIS IN EVERY MELEE UNIT, SO THEY CAN REECEIVE DAMAGE WHEN ATTACKING 
AttackNotification Swordsman::Attack(UnitBase * target)
{
	AttackNotification targetNotification = UnitBase::Attack(target);
	AttackNotification attackerNotification = ReceiveDamage(targetNotification.RiposteDamage);

	targetNotification.AttackerIsDead = attackerNotification.TargetIsDead;
	targetNotification.CanMove = true;

	return targetNotification;
}

AttackNotification Swordsman::Attack(DistrictBase * target)
{
	AttackNotification targetNotification = UnitBase::Attack(target);
	AttackNotification attackerNotification = ReceiveDamage(targetNotification.RiposteDamage);

	if (attackerNotification.TargetIsDead)
	{
		targetNotification.AttackerIsDead = true;
	}

	targetNotification.CanMove = true;
	return targetNotification;
}

boost::property_tree::ptree Swordsman::Serialize()
{
	return boost::property_tree::ptree();
}
