#include "unitRange.h"

UnitRange::UnitRange(int ownerID, int attackRange)
	: Unit(ownerID, attackRange, 25)
{
}

UnitRange::~UnitRange()
{
}

AttackNotification UnitRange::Attack(Actor* target)
{
	AttackNotification targetNotification = target->ReceiveDamage(GetAttackDamage());

	return targetNotification;
}
