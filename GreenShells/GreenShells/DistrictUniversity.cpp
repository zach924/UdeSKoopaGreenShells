#include "GameSession.h"
#include <iostream>
#include "DistrictUniversity.h"
#include "Player.h"

DistrictUniversity::DistrictUniversity(int owner)
    : District<DistrictUniversity>(owner, HEALTH, ATTACK_DAMAGE, VIEW_RANGE, NAME, DISTRICT_TYPE, FOOD_COST, 0, 0, 0, NO_UPGRADE, 0, SCIENCE_BONUS, 0)
{
}

std::shared_ptr<DistrictBase> DistrictUniversity::Clone()
{
    return std::shared_ptr<DistrictBase> { new DistrictUniversity{ *this } };
}

void DistrictUniversity::LoadTexture()
{
    try
    {
        m_Texture.LoadFromFile("..\\Sprite\\Districts\\64x64\\university.bmp");
    }
    catch (std::exception e)
    {
        std::string msg{ e.what() };
        std::cout << msg << std::endl;
    }
}

DistrictUniversity::~DistrictUniversity()
{
}

bool DistrictUniversity::CanUpgrade()
{
    return false;
}

std::shared_ptr<DistrictUniversity> DistrictUniversity::Deserialize(boost::property_tree::ptree node)
{
    auto district = std::shared_ptr<DistrictUniversity>{ new DistrictUniversity(node.get<int>("<xmlattr>.O")) };
    district->m_health = node.get<int>("<xmlattr>.H");

    return district;
}
