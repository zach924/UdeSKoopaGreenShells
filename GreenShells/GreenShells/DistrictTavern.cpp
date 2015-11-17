#include "GameSession.h"
#include <iostream>
#include "DistrictTavern.h"
#include "Player.h"

const char* DistrictTavern::NAME = "Tavern";

DistrictTavern::DistrictTavern(int owner)
    : District<DistrictTavern>(owner, HEALTH, ATTACK_DAMAGE, FOOD_COST, FOOD_BONUS, SCIENCE_BONUS, WEAPON_BONUS)
{
}

DistrictBase* DistrictTavern::Clone()
{
    return new DistrictTavern{ *this };
}

void DistrictTavern::LoadTexture()
{
    try
    {
        m_Texture.LoadFromFile("..\\Sprite\\Districts\\64x64\\tavern.bmp");
    }
    catch (std::exception e)
    {
        std::string msg{ e.what() };
        std::cout << msg << std::endl;
    }
}

DistrictTavern::~DistrictTavern()
{
}

void DistrictTavern::Repair(int repairValue)
{
    m_health = std::min(m_health + repairValue, HEALTH);
}

bool DistrictTavern::CanUpgrade()
{
    return false;
}

int DistrictTavern::GetMaxHealth()
{
    return HEALTH;
}

const char * DistrictTavern::GetName()
{
    return NAME;
}

int DistrictTavern::GetTypeAsInt()
{
    return DISTRICT_TYPE;
}

DistrictTavern * DistrictTavern::Deserialize(boost::property_tree::ptree node)
{
    DistrictTavern* tavern = new DistrictTavern(node.get<int>("<xmlattr>.O"));
    tavern->m_health = node.get<int>("<xmlattr>.H");

    return tavern;
}



