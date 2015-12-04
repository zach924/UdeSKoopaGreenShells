#include "DistrictCityCenter.h"
#include <algorithm>
#include <iostream>

DistrictCityCenter::DistrictCityCenter(int owner)
    : District<DistrictCityCenter>(owner, HEALTH, ATTACK_DAMAGE, VIEW_RANGE, NAME, DISTRICT_TYPE, FOOD_COST, WEAPON_YIELD, FOOD_YIELD, SCIENCE_YIELD)
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
        m_Texture.LoadFromFile("Ressources\\Sprite\\Districts\\64x64\\city.bmp");
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

bool DistrictCityCenter::CanUpgrade()
{
    return false; // City center cannot be upgraded
}

std::shared_ptr<DistrictCityCenter> DistrictCityCenter::Deserialize(boost::property_tree::ptree node)
{
    auto district = std::shared_ptr<DistrictCityCenter>{ new DistrictCityCenter(node.get<int>("<xmlattr>.O")) };
    district->m_health = node.get<int>("<xmlattr>.H");

    return district;
}