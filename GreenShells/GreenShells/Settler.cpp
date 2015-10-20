#include "Settler.h"
#include <iostream>

Settler::Settler(int owner)
	: Unit<Settler>(owner, HEALTH, MELEE_ATTACK_RANGE, ATTACK_DAMAGE)
{
}

Settler::~Settler()
{
}

void Settler::LoadTexture()
{
	try
	{
		m_Texture.LoadFromFile("..\\Sprite\\Units\\64x64\\Cannon.bmp"); //TODO Change to settler icon
	}
	catch (std::exception e)
	{
		std::string msg{ e.what() };
		std::cout << msg << std::endl;
	}
}

void Settler::Heal(int health)
{
	m_health = std::min(m_health + health, HEALTH);
}

// NEED TO PUT THIS IN EVERY MELEE UNIT, SO THEY CAN REECEIVE DAMAGE WHEN ATTACKING 
AttackNotification Settler::Attack(UnitBase * target)
{
	AttackNotification targetNotification = UnitBase::Attack(target);
	AttackNotification attackerNotification = ReceiveDamage(targetNotification.RiposteDamage);

	targetNotification.AttackerIsDead = attackerNotification.TargetIsDead;
	targetNotification.CanMove = true;

	return targetNotification;
}

AttackNotification Settler::Attack(DistrictBase * target)
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

boost::property_tree::ptree Settler::Serialize()
{
	return boost::property_tree::ptree();
}
