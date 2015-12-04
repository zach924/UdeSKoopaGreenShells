#include "GameSession.h"
#include <iostream>
#include "DistrictWarehouse.h"
#include "Player.h"

DistrictWarehouse::DistrictWarehouse(int owner)
    : District<DistrictWarehouse>(owner, HEALTH, ATTACK_DAMAGE, VIEW_RANGE, NAME, DISTRICT_TYPE, FOOD_COST, 0, 0, 0, NO_UPGRADE, FOOD_BONUS, 0, 0)
{
}

std::shared_ptr<DistrictBase> DistrictWarehouse::Clone()
{
    return std::shared_ptr<DistrictBase> { new DistrictWarehouse{ *this } };
}

void DistrictWarehouse::LoadTexture()
{
    try
    {
        m_Texture.LoadFromFile("Resources\\Sprite\\Districts\\64x64\\warehouse.bmp");
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

bool DistrictWarehouse::CanUpgrade()
{
    return false;
}

std::shared_ptr<DistrictWarehouse> DistrictWarehouse::Deserialize(boost::property_tree::ptree node)
{
    auto district = std::shared_ptr<DistrictWarehouse>{ new DistrictWarehouse(node.get<int>("<xmlattr>.O")) };
    district->m_health = node.get<int>("<xmlattr>.H");

    return district;
}
