#pragma once
#include "Unit.h"

class UnitMelee : public Unit
{
public:
	UnitMelee(int& ownerID);
	~UnitMelee();
};