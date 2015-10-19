#include "CityCenter.h"
#include <algorithm>

CityCenter::CityCenter(int owner)
	: District<CityCenter>(owner, HEALTH, ATTACK_DAMAGE)
{
}

CityCenter::~CityCenter()
{
}

void CityCenter::ChangeOwner(int owner)
{
	m_ownerID = owner;
	m_health = HEALTH;
}

int CityCenter::GetTypeAsInt()
{
	return DISTRICT_TYPE;
}

void CityCenter::Repair(int repairValue)
{
	m_health = std::min(m_health + repairValue, HEALTH);
}
