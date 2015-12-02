#include "GameSession.h"
#include <iostream>
#include "DistrictMilitaryTent.h"
#include "Player.h"

DistrictMilitaryTent::DistrictMilitaryTent(int owner)
    : District<DistrictMilitaryTent>(owner, HEALTH, ATTACK_DAMAGE, VIEW_RANGE, NAME, DISTRICT_TYPE, FOOD_COST, 0, 0, 0, NO_UPGRADE, 0, 0, WEAPON_BONUS)
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

bool DistrictMilitaryTent::CanUpgrade()
{
    return false;
}

std::shared_ptr<DistrictMilitaryTent> DistrictMilitaryTent::Deserialize(boost::property_tree::ptree node)
{
    auto district = std::shared_ptr<DistrictMilitaryTent>{ new DistrictMilitaryTent(node.get<int>("<xmlattr>.O")) };
    district->m_health = node.get<int>("<xmlattr>.H");

    return district;
}




