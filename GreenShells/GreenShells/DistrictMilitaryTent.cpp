#include "GameSession.h"
#include <iostream>
#include "DistrictMilitaryTent.h"
#include "Player.h"

const char* DistrictMilitaryTent::NAME = "Military Tent";

DistrictMilitaryTent::DistrictMilitaryTent(int owner)
    : District<DistrictMilitaryTent>(owner, HEALTH, ATTACK_DAMAGE, FOOD_COST, FOOD_BONUS, SCIENCE_BONUS, WEAPON_BONUS)
{
}

std::shared_ptr<DistrictBase> DistrictMilitaryTent::Clone()
{
    return std::shared_ptr<DistrictBase> { new DistrictMilitaryTent{ *this } };
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

int DistrictMilitaryTent::GetViewRange()
{
    return VIEW_RANGE;
}

std::shared_ptr<DistrictMilitaryTent> DistrictMilitaryTent::Deserialize(boost::property_tree::ptree node)
{
    auto district = std::shared_ptr<DistrictMilitaryTent>{ new DistrictMilitaryTent(node.get<int>("<xmlattr>.O")) };
    district->m_health = node.get<int>("<xmlattr>.H");

    return district;
}




