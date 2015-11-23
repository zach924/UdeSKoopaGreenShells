#include "GameSession.h"
#include <iostream>
#include "DistrictWarehouse.h"
#include "Player.h"

const char* DistrictWarehouse::NAME = "Warehouse";

DistrictWarehouse::DistrictWarehouse(int owner)
    : District<DistrictWarehouse>(owner, HEALTH, ATTACK_DAMAGE, FOOD_COST, FOOD_BONUS, SCIENCE_BONUS, WEAPON_BONUS)
{
}

DistrictBase* DistrictWarehouse::Clone()
{
    return new DistrictWarehouse{ *this };
}

void DistrictWarehouse::LoadTexture()
{
    try
    {
        m_Texture.LoadFromFile("..\\Sprite\\Districts\\64x64\\warehouse.bmp");
    }
    catch (std::exception e)
    {
        std::string msg{ e.what() };
        std::cout << msg << std::endl;
    }
}

DistrictWarehouse::~DistrictWarehouse()
{
}

void DistrictWarehouse::Repair(int repairValue)
{
    m_health = std::min(m_health + repairValue, HEALTH);
}

bool DistrictWarehouse::CanUpgrade()
{
    return false;
}

int DistrictWarehouse::GetMaxHealth()
{
    return HEALTH;
}

const char * DistrictWarehouse::GetName()
{
    return NAME;
}

int DistrictWarehouse::GetTypeAsInt()
{
    return DISTRICT_TYPE;
}

int DistrictWarehouse::GetViewRange()
{
    return VIEW_RANGE;
}

DistrictWarehouse * DistrictWarehouse::Deserialize(boost::property_tree::ptree node)
{
    DistrictWarehouse* warehouse = new DistrictWarehouse(node.get<int>("<xmlattr>.O"));
    warehouse->m_health = node.get<int>("<xmlattr>.H");

    return warehouse;
}
