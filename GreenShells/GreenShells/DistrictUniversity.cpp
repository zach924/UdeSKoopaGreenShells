#include "GameSession.h"
#include <iostream>
#include "DistrictUniversity.h"
#include "Player.h"

const char* DistrictUniversity::NAME = "University";

DistrictUniversity::DistrictUniversity(int owner)
    : District<DistrictUniversity>(owner, HEALTH, ATTACK_DAMAGE, FOOD_COST)
{
}

DistrictBase* DistrictUniversity::Clone()
{
    return new DistrictUniversity{ *this };
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

DistrictUniversity * DistrictUniversity::Deserialize(boost::property_tree::ptree node)
{
    DistrictUniversity* uni = new DistrictUniversity(node.get<int>("<xmlattr>.O"));
    uni->m_health = node.get<int>("<xmlattr>.H");

    return uni;
}


