#pragma once
#include "Unit.h"

class UnitRange : public Unit
{

public :
	UnitRange(int& ownerID, int attackRange);
	~UnitRange();
};