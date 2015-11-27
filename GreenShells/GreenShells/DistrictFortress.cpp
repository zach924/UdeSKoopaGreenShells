#include "GameSession.h"
#include <iostream>
#include "DistrictFortress.h"
#include "Player.h"

const char* DistrictFortress::NAME = "Fortress";

DistrictFortress::DistrictFortress(int owner)
    : District<DistrictFortress>(owner, HEALTH, ATTACK_DAMAGE, FOOD_COST, FOOD_BONUS, SCIENCE_BONUS, WEAPON_BONUS)
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
        m_Texture.LoadFromFile("..\\Sprite\\Districts\\64x64\\fortress.bmp");
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

void DistrictFortress::Repair(int repairValue)
{
    m_health = std::min(m_health + repairValue, HEALTH);
}

bool DistrictFortress::CanUpgrade()
{
    return false;
}

int DistrictFortress::GetMaxHealth()
{
    return HEALTH;
}

const char * DistrictFortress::GetName()
{
    return NAME;
}

int DistrictFortress::GetTypeAsInt()
{
    return DISTRICT_TYPE;
}

int DistrictFortress::GetViewRange()
{
    return VIEW_RANGE;
}

std::shared_ptr<DistrictFortress> DistrictFortress::Deserialize(boost::property_tree::ptree node)
{
    auto district = std::shared_ptr<DistrictFortress>{ new DistrictFortress(node.get<int>("<xmlattr>.O")) };
    district->m_health = node.get<int>("<xmlattr>.H");

    return district;
}

