#include "UnitMelee.h"
#include "GameSession.h"
#include "MapLocal.h"

UnitMelee::UnitMelee(int ownerID)
	: Unit(ownerID, Unit::MELEE_ATTACK_RANGE)
	
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

	return targetNotification;
}

AttackNotification UnitMelee::ReceiveDamage(int damage)
{
	m_health -= damage;

	return AttackNotification{ GetAttackDamage() / 2, (m_health <= 0), true };
}
