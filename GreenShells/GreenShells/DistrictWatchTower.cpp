#include "GameSession.h"
#include <iostream>
#include "DistrictWatchTower.h"
#include "Player.h"

const char* DistrictWatchTower::NAME = "Watch Tower";

DistrictWatchTower::DistrictWatchTower(int owner)
    : District<DistrictWatchTower>(owner, HEALTH, ATTACK_DAMAGE, FOOD_COST, FOOD_BONUS, SCIENCE_BONUS, WEAPON_BONUS)
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
        m_Texture.LoadFromFile("..\\Sprite\\Districts\\64x64\\watchtower.bmp");
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

void DistrictWatchTower::Repair(int repairValue)
{
    m_health = std::min(m_health + repairValue, HEALTH);
}

bool DistrictWatchTower::CanUpgrade()
{
    return false;
}

int DistrictWatchTower::GetMaxHealth()
{
    return HEALTH;
}

const char * DistrictWatchTower::GetName()
{
    return NAME;
}

int DistrictWatchTower::GetTypeAsInt()
{
    return DISTRICT_TYPE;
}

int DistrictWatchTower::GetViewRange()
{
    return VIEW_RANGE;
}

std::shared_ptr<DistrictWatchTower> DistrictWatchTower::Deserialize(boost::property_tree::ptree node)
{
    auto district = std::shared_ptr<DistrictWatchTower>{ new DistrictWatchTower(node.get<int>("<xmlattr>.O")) };
    district->m_health = node.get<int>("<xmlattr>.H");

    return district;
}
