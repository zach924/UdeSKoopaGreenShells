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

boost::property_tree::ptree Farm::Serialize()
{
	return boost::property_tree::ptree();
}