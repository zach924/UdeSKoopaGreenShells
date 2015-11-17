#include "GameSession.h"
#include <iostream>
#include "DistrictMilitaryTent.h"
#include "Player.h"

const char* DistrictMilitaryTent::NAME = "Military Tent";

DistrictMilitaryTent::DistrictMilitaryTent(int owner)
    : District<DistrictMilitaryTent>(owner, HEALTH, ATTACK_DAMAGE, FOOD_COST, FOOD_BONUS, SCIENCE_BONUS, WEAPON_BONUS)
{
}

DistrictBase* DistrictMilitaryTent::Clone()
{
    return new DistrictMilitaryTent{ *this };
}

void DistrictMilitaryTent::LoadTexture()
{
    try
    {
        m_Texture.LoadFromFile("..\\Sprite\\Districts\\64x64\\wartent.bmp");
    }
    catch (std::exception e)
    {
        std::string msg{ e.what() };
        std::cout << msg << std::endl;
    }
}

DistrictMilitaryTent::~DistrictMilitaryTent()
{
}

void DistrictMilitaryTent::Repair(int repairValue)
{
    m_health = std::min(m_health + repairValue, HEALTH);
}

bool DistrictMilitaryTent::CanUpgrade()
{
    return false;
}

int DistrictMilitaryTent::GetMaxHealth()
{
    return HEALTH;
}

const char * DistrictMilitaryTent::GetName()
{
    return NAME;
}

int DistrictMilitaryTent::GetTypeAsInt()
{
    return DISTRICT_TYPE;
}

DistrictMilitaryTent * DistrictMilitaryTent::Deserialize(boost::property_tree::ptree node)
{
    DistrictMilitaryTent* militaryTent = new DistrictMilitaryTent(node.get<int>("<xmlattr>.O"));
    militaryTent->m_health = node.get<int>("<xmlattr>.H");

    return militaryTent;
}




