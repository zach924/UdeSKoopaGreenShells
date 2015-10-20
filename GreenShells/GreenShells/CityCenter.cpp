#include "CityCenter.h"
#include <algorithm>
#include <iostream>

CityCenter::CityCenter(int owner)
	: District<CityCenter>(owner, HEALTH, ATTACK_DAMAGE)
{
}


void CityCenter::LoadTexture()
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

CityCenter::~CityCenter()
{
}

void CityCenter::ChangeOwner(int owner)
{
	m_ownerID = owner;
	m_health = HEALTH;
}

void CityCenter::Repair(int repairValue)
{
	m_health = std::min(m_health + repairValue, HEALTH);
}

boost::property_tree::ptree CityCenter::Serialize()
{
	return boost::property_tree::ptree();
}
