#include "DistrictDefensive.h"

DistrictDefensive::DistrictDefensive(int ownerID, int attackDamage)
	: District(ownerID)
{
	SetAttackDamage(attackDamage);
}

DistrictDefensive::~DistrictDefensive()
{
}

