#include "GameSession.h"
#include <iostream>
#include "DistrictUniversity.h"
#include "Player.h"

const char* DistrictUniversity::NAME = "University";

DistrictUniversity::DistrictUniversity(int owner)
    : District<DistrictUniversity>(owner, HEALTH, ATTACK_DAMAGE, FOOD_COST)
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

void DistrictUniversity::Repair(int repairValue)
{
    m_health = std::min(m_health + repairValue, HEALTH);
}

bool DistrictUniversity::CanUpgrade()
{
    return false;
}

int DistrictUniversity::GetMaxHealth()
{
    return HEALTH;
}

const char * DistrictUniversity::GetName()
{
    return NAME;
}

int DistrictUniversity::GetTypeAsInt()
{
    return DISTRICT_TYPE;
}

int DistrictUniversity::GetViewRange()
{
    return VIEW_RANGE;
}

std::shared_ptr<DistrictUniversity> DistrictUniversity::Deserialize(boost::property_tree::ptree node)
{
    auto district = std::shared_ptr<DistrictUniversity>{ new DistrictUniversity(node.get<int>("<xmlattr>.O")) };
    district->m_health = node.get<int>("<xmlattr>.H");

    return district;
}
