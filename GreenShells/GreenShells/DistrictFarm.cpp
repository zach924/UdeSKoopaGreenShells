#include "DistrictFarm.h"
#include <iostream>

const char* DistrictFarm::NAME = "Farm";

DistrictFarm::DistrictFarm(int owner)
    : District<DistrictFarm>(owner, HEALTH, NORMAL_DISTRICT_ATTACK_DMG)
{
}

DistrictBase* DistrictFarm::Clone()
{
    return new DistrictFarm{ *this };
}

void DistrictFarm::LoadTexture()
{
    try
    {
        m_Texture.LoadFromFile("..\\Sprite\\Districts\\64x64\\farm.bmp");
	}
    catch (std::exception e)
    {
        std::string msg{ e.what() };
        std::cout << msg << std::endl;
    }
}

DistrictFarm::~DistrictFarm()
{
}

void DistrictFarm::Repair(int repairValue)
{
    m_health = std::min(m_health + repairValue, HEALTH);
}

bool DistrictFarm::CanUpgrade()
{
    return false; // TODO : Need to get the flag of player class
}

int DistrictFarm::GetMaxHealth()
{
	return HEALTH;
}

const char * DistrictFarm::GetName()
{
	return NAME;
}

int DistrictFarm::GetTypeAsInt()
{
    return DISTRICT_TYPE;
}

DistrictFarm * DistrictFarm::Deserialize(boost::property_tree::ptree node)
{
    DistrictFarm* farm = new DistrictFarm(node.get<int>("<xmlattr>.O"));
    farm->m_health = node.get<int>("<xmlattr>.H");

    return farm;
}