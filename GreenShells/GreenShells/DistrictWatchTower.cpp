#include "GameSession.h"
#include <iostream>
#include "DistrictWatchTower.h"
#include "Player.h"

DistrictWatchTower::DistrictWatchTower(int owner)
    : District<DistrictWatchTower>(owner, HEALTH, ATTACK_DAMAGE, VIEW_RANGE, NAME, DISTRICT_TYPE, FOOD_COST)
{
}

std::shared_ptr<DistrictBase> DistrictWatchTower::Clone()
{
    return std::shared_ptr<DistrictBase> { new DistrictWatchTower{ *this } };
}

void DistrictWatchTower::LoadTexture()
{
    try
    {
        m_Texture.LoadFromFile("Ressources\\Sprite\\Districts\\64x64\\watchtower.bmp");
    }
    catch (std::exception e)
    {
        std::string msg{ e.what() };
        std::cout << msg << std::endl;
    }
}

DistrictWatchTower::~DistrictWatchTower()
{
}

bool DistrictWatchTower::CanUpgrade()
{
    return false;
}

std::shared_ptr<DistrictWatchTower> DistrictWatchTower::Deserialize(boost::property_tree::ptree node)
{
    auto district = std::shared_ptr<DistrictWatchTower>{ new DistrictWatchTower(node.get<int>("<xmlattr>.O")) };
    district->m_health = node.get<int>("<xmlattr>.H");

    return district;
}
