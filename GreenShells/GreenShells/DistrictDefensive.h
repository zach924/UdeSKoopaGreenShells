#pragma once
#include "District.h"

class DistrictDefensive : public District
{
public:
	DistrictDefensive(int ownerID, int attackDamage);
	~DistrictDefensive();

};