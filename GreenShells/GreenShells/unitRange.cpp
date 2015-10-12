#include "unitRange.h"

UnitRange::UnitRange(int ownerID, int attackRange)
	: Unit(ownerID, attackRange)
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
