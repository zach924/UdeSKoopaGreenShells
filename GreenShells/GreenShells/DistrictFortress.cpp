#include "GameSession.h"
#include <iostream>
#include "DistrictFortress.h"
#include "Player.h"

DistrictFortress::DistrictFortress(int owner)
    : District<DistrictFortress>(owner, HEALTH, ATTACK_DAMAGE, VIEW_RANGE, NAME, DISTRICT_TYPE, FOOD_COST, WEAPON_YIELD, FOOD_YIELD, SCIENCE_YIELD)
{
}

std::shared_ptr<DistrictBase> DistrictFortress::Clone()
{
    return std::shared_ptr<DistrictBase> { new DistrictFortress{ *this } };
}

void DistrictFortress::LoadTexture()
{
    try
    {
        m_Texture.LoadFromFile("Resources\\Sprite\\Districts\\64x64\\fortress.bmp");
    }
    catch (std::exception e)
    {
        std::string msg{ e.what() };
        std::cout << msg << std::endl;
    }
}

DistrictFortress::~DistrictFortress()
{
}

bool DistrictFortress::CanUpgrade()
{
    return false;
}

std::shared_ptr<DistrictFortress> DistrictFortress::Deserialize(boost::property_tree::ptree node)
{
    auto district = std::shared_ptr<DistrictFortress>{ new DistrictFortress(node.get<int>("<xmlattr>.O")) };
    district->m_health = node.get<int>("<xmlattr>.H");

    return district;
}

