#include "DistrictCityCenter.h"
#include <algorithm>
#include <iostream>
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#ifdef _DEBUG
#define DEBUG_CLIENTBLOCK   new( _CLIENT_BLOCK, __FILE__, __LINE__)
#else
#define DEBUG_CLIENTBLOCK
#endif // _DEBUG

#ifdef _DEBUG
#define new DEBUG_CLIENTBLOCK
#endif
DistrictCityCenter::DistrictCityCenter(int owner)
	: District<DistrictCityCenter>(owner, HEALTH, ATTACK_DAMAGE)
{
}

DistrictBase* DistrictCityCenter::Clone()
{
	return new DistrictCityCenter{ *this };
}

void DistrictCityCenter::LoadTexture()
{
    try
    {
        m_Texture.LoadFromFile("..\\Sprite\\Districts\\64x64\\City.bmp");
    }
    catch (std::exception e)
    {
        std::string msg{ e.what() };
        std::cout << msg << std::endl;
    }
}

DistrictCityCenter::~DistrictCityCenter()
{
}

void DistrictCityCenter::ChangeOwner(int owner)
{
	m_ownerID = owner;
	m_health = HEALTH;
}

int DistrictCityCenter::GetTypeAsInt()
{
	return DISTRICT_TYPE;
}

void DistrictCityCenter::Repair(int repairValue)
{
	m_health = std::min(m_health + repairValue, HEALTH);
}

DistrictCityCenter * DistrictCityCenter::Deserialize(boost::property_tree::ptree node)
{
	DistrictCityCenter* cityCenter = new DistrictCityCenter(node.get<int>("<xmlattr>.O"));
	cityCenter->m_health = node.get<int>("<xmlattr>.H");

	return cityCenter;
}
