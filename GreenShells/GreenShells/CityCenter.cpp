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

CityCenter * CityCenter::Deserialize(boost::property_tree::ptree node)
{
	CityCenter* cityCenter = new CityCenter(node.get<int>("<xmlattr>.O"));
	cityCenter->m_health = node.get<int>("<xmlattr>.H");

	return cityCenter;
}
