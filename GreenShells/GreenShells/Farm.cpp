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

Farm * Farm::Deserialize(boost::property_tree::ptree node)
{
	Farm* farm = new Farm(node.get<int>("<xmlattr>.O"));
	farm->m_health = node.get<int>("<xmlattr>.H");

	return farm;
}
