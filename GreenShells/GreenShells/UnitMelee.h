#pragma once
#include "Unit.h"

class UnitMelee : public Unit
{
public:
	UnitMelee(int ownerID, int attackDmg);
	~UnitMelee();

	virtual AttackNotification Attack(Actor* target);
	virtual AttackNotification ReceiveDamage(int damage);
};