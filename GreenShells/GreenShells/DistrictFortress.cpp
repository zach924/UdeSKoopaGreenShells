#include "GameSession.h"
#include <iostream>
#include "DistrictFortress.h"
#include "Player.h"

const char* DistrictFortress::NAME = "Fortress";

DistrictFortress::DistrictFortress(int owner)
    : District<DistrictFortress>(owner, HEALTH, ATTACK_DAMAGE, FOOD_COST, FOOD_BONUS, SCIENCE_BONUS, WEAPON_BONUS)
{
}

DistrictBase* DistrictFortress::Clone()
{
    return new DistrictFortress{ *this };
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

DistrictFortress * DistrictFortress::Deserialize(boost::property_tree::ptree node)
{
    DistrictFortress* fort = new DistrictFortress(node.get<int>("<xmlattr>.O"));
    fort->m_health = node.get<int>("<xmlattr>.H");

    return fort;
}

