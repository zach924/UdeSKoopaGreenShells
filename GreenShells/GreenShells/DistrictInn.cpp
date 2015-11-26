#include "GameSession.h"
#include <iostream>
#include "DistrictInn.h"
#include "Player.h"

const char* DistrictInn::NAME = "Inn";

DistrictInn::DistrictInn(int owner)
    : District<DistrictInn>(owner, HEALTH, ATTACK_DAMAGE, FOOD_COST, FOOD_BONUS, SCIENCE_BONUS, WEAPON_BONUS)
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
        m_Texture.LoadFromFile("..\\Sprite\\Districts\\64x64\\inn.bmp");
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

void DistrictInn::Repair(int repairValue)
{
    m_health = std::min(m_health + repairValue, HEALTH);
}

bool DistrictInn::CanUpgrade()
{
    return false;
}

int DistrictInn::GetMaxHealth()
{
    return HEALTH;
}

const char * DistrictInn::GetName()
{
    return NAME;
}

int DistrictInn::GetTypeAsInt()
{
    return DISTRICT_TYPE;
}

int DistrictInn::GetViewRange()
{
    return VIEW_RANGE;
}

std::shared_ptr<DistrictInn> DistrictInn::Deserialize(boost::property_tree::ptree node)
{
    auto district = std::shared_ptr<DistrictInn>{ new DistrictInn(node.get<int>("<xmlattr>.O")) };
    district->m_health = node.get<int>("<xmlattr>.H");

    return district;
}



