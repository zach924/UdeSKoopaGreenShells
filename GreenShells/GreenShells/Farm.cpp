#include "Farm.h"

Farm::Farm(int owner)
	: District<Farm>(owner, HEALTH, NORMAL_DISTRICT_ATTACK_DMG)
{
}

Farm::~Farm()
{
}

void Farm::Repair(int repairValue)
{
	m_health = std::min(m_health + repairValue, HEALTH);
}

int Farm::GetTypeAsInt()
{
	return DISTRICT_TYPE;
}