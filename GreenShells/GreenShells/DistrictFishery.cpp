#include "GameSession.h"
#include <iostream>
#include "DistrictFishery.h"
#include "Player.h"

DistrictFishery::DistrictFishery(int owner)
    : District<DistrictFishery>(owner, HEALTH, ATTACK_DAMAGE, VIEW_RANGE, NAME, DISTRICT_TYPE, FOOD_COST, WEAPON_YIELD, FOOD_YIELD, SCIENCE_YIELD)
{
}

std::shared_ptr<DistrictBase> DistrictFishery::Clone()
{
    return std::shared_ptr<DistrictBase> { new DistrictFishery{ *this } };
}

void DistrictFishery::LoadTexture()
{
    try
    {
        m_Texture.LoadFromFile("Resources\\Sprite\\Districts\\64x64\\fishery.bmp");
    }
    catch (std::exception e)
    {
        std::string msg{ e.what() };
        std::cout << msg << std::endl;
    }
}

DistrictFishery::~DistrictFishery()
{
}

bool DistrictFishery::CanUpgrade()
{
    return false;
}

std::shared_ptr<DistrictFishery> DistrictFishery::Deserialize(boost::property_tree::ptree node)
{
    auto district = std::shared_ptr<DistrictFishery>{ new DistrictFishery(node.get<int>("<xmlattr>.O")) };
    district->m_health = node.get<int>("<xmlattr>.H");

    return district;
}

