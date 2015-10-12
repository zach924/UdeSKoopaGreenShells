#include <iostream>

#include "UnitMelee.h"
#include "GameSession.h"
#include "MapLocal.h"

UnitMelee::UnitMelee(int ownerID, int attackDmg)
	: Unit(ownerID, Unit::MELEE_ATTACK_RANGE, attackDmg)
	
{

}
UnitMelee::~UnitMelee()
{
}

AttackNotification UnitMelee::Attack(Actor * target)
{
	AttackNotification targetNotification = target->ReceiveDamage(GetAttackDamage());
	AttackNotification attackerNotification = ReceiveDamage(targetNotification.RiposteDamage);

	if (attackerNotification.TargetIsDead)
	{
		targetNotification.AttackerIsDead = true;
	}

	targetNotification.CanMove = true;
	return targetNotification;
}

AttackNotification UnitMelee::ReceiveDamage(int damage)
{
	m_health -= damage;

	if (m_health <= 0)
		std::cout << "A melee unit die : Player " << m_ownerID << std::endl;

	return AttackNotification{ GetAttackDamage() / 2, (m_health <= 0), true };
}
