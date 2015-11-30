#include "GameSession.h"
#include <iostream>
#include "DistrictTavern.h"
#include "Player.h"

DistrictTavern::DistrictTavern(int owner)
    : District<DistrictTavern>(owner, HEALTH, ATTACK_DAMAGE, VIEW_RANGE, NAME, DISTRICT_TYPE, FOOD_COST, WEAPON_YIELD, FOOD_YIELD, SCIENCE_YIELD)
{
}

std::shared_ptr<DistrictBase> DistrictTavern::Clone()
{
    return std::shared_ptr<DistrictBase> { new DistrictTavern{ *this } };
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

bool DistrictTavern::CanUpgrade()
{
    return false;
}

std::shared_ptr<DistrictTavern> DistrictTavern::Deserialize(boost::property_tree::ptree node)
{
    auto district = std::shared_ptr<DistrictTavern>{ new DistrictTavern(node.get<int>("<xmlattr>.O")) };
    district->m_health = node.get<int>("<xmlattr>.H");

    return district;
}
