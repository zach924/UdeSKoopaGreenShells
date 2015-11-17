#include "GameSession.h"
#include <iostream>
#include "DistrictWatchTower.h"
#include "Player.h"

const char* DistrictWatchTower::NAME = "Watch Tower";

DistrictWatchTower::DistrictWatchTower(int owner)
    : District<DistrictWatchTower>(owner, HEALTH, ATTACK_DAMAGE, FOOD_COST, FOOD_BONUS, SCIENCE_BONUS, WEAPON_BONUS)
{
}

DistrictBase* DistrictWatchTower::Clone()
{
    return new DistrictWatchTower{ *this };
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

DistrictWatchTower * DistrictWatchTower::Deserialize(boost::property_tree::ptree node)
{
    DistrictWatchTower* watchtower = new DistrictWatchTower(node.get<int>("<xmlattr>.O"));
    watchtower->m_health = node.get<int>("<xmlattr>.H");

    return watchtower;
}


