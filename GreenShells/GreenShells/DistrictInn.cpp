#include "GameSession.h"
#include <iostream>
#include "DistrictInn.h"
#include "Player.h"

DistrictInn::DistrictInn(int owner)
    : District<DistrictInn>(owner, HEALTH, ATTACK_DAMAGE, VIEW_RANGE, NAME, DISTRICT_TYPE, FOOD_COST, WEAPON_YIELD, FOOD_YIELD, SCIENCE_YIELD)
{
}

std::shared_ptr<DistrictBase> DistrictInn::Clone()
{
    return std::shared_ptr<DistrictBase> { new DistrictInn{ *this } };
}

void DistrictInn::LoadTexture()
{
    try
    {
        m_Texture.LoadFromFile("Ressources\\Sprite\\Districts\\64x64\\inn.bmp");
    }
    catch (std::exception e)
    {
        std::string msg{ e.what() };
        std::cout << msg << std::endl;
    }
}

DistrictInn::~DistrictInn()
{
}

bool DistrictInn::CanUpgrade()
{
    return false;
}

std::shared_ptr<DistrictInn> DistrictInn::Deserialize(boost::property_tree::ptree node)
{
    auto district = std::shared_ptr<DistrictInn>{ new DistrictInn(node.get<int>("<xmlattr>.O")) };
    district->m_health = node.get<int>("<xmlattr>.H");

    return district;
}



