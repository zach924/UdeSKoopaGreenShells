#include "DistrictCityCenter.h"
#include <algorithm>
#include <iostream>

const char* DistrictCityCenter::NAME = "City Center";

DistrictCityCenter::DistrictCityCenter(int owner)
    : District<DistrictCityCenter>(owner, HEALTH, ATTACK_DAMAGE, VIEW_RANGE, FOOD_COST, WEAPON_YIELD, FOOD_YIELD, SCIENCE_YIELD)
{
}

std::shared_ptr<DistrictBase> DistrictCityCenter::Clone()
{
    return std::shared_ptr<DistrictBase> { new DistrictCityCenter{ *this } };
}

void DistrictCityCenter::LoadTexture()
{
    try
    {
        m_Texture.LoadFromFile("..\\Sprite\\Districts\\64x64\\city.bmp");
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

void DistrictCityCenter::ChangeOwner(int newOwner)
{
    DistrictBase::ChangeOwner(newOwner);
    m_health = HEALTH;
}

int DistrictCityCenter::GetMaxHealth()
{
    return HEALTH;
}

const char * DistrictCityCenter::GetName()
{
    return NAME;
}

int DistrictCityCenter::GetTypeAsInt()
{
    return DISTRICT_TYPE;
}

int DistrictCityCenter::GetViewRange()
{
    return VIEW_RANGE;
}

void DistrictCityCenter::Repair(int repairValue)
{
    m_health = std::min(m_health + repairValue, HEALTH);
}

bool DistrictCityCenter::CanUpgrade()
{
    return false; // City center cannot be upgraded
}

std::shared_ptr<DistrictCityCenter> DistrictCityCenter::Deserialize(boost::property_tree::ptree node)
{
    auto cityCenter = std::shared_ptr<DistrictCityCenter>{ new DistrictCityCenter(node.get<int>("<xmlattr>.O")) };
    cityCenter->m_health = node.get<int>("<xmlattr>.H");

    return cityCenter;
}