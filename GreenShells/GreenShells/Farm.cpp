#include "Farm.h"
#include <iostream>

Farm::Farm(int owner)
	: District<Farm>(owner, HEALTH, NORMAL_DISTRICT_ATTACK_DMG)
{
}

void Farm::LoadTexture()
{
    try
    {
        m_Texture.LoadFromFile("..\\Sprite\\Districts\\64x64\\Farm.bmp");
    }
    catch (std::exception e)
    {
        std::string msg{ e.what() };
        std::cout << msg << std::endl;
    }
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