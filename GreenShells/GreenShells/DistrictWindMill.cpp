#include "GameSession.h"
#include <iostream>
#include "DistrictWindMill.h"
#include "Player.h"
#include "Map.h"
#include "DistrictWarehouse.h"

DistrictWindMill::DistrictWindMill(int owner)
    : District<DistrictWindMill>(owner, HEALTH, ATTACK_DAMAGE, VIEW_RANGE, NAME, DISTRICT_TYPE, FOOD_COST, WEAPON_YIELD, FOOD_YIELD, SCIENCE_YIELD, UPGRADE_TYPE)
{
}

std::shared_ptr<DistrictBase> DistrictWindMill::Clone()
{
    return std::shared_ptr<DistrictBase> { new DistrictWindMill{ *this } };
}

void DistrictWindMill::LoadTexture()
{
    try
    {
        m_Texture.LoadFromFile("Ressources\\Sprite\\Districts\\64x64\\windmill.bmp");
    }
    catch (std::exception e)
    {
        std::string msg{ e.what() };
        std::cout << msg << std::endl;
    }
}

DistrictWindMill::~DistrictWindMill()
{
}

void DistrictWindMill::Repair(int repairValue)
{
    m_health = std::min(m_health + repairValue, HEALTH);
}

bool DistrictWindMill::CanUpgrade()
{
    auto player = GameSession::GetInstance().GetWorldState()->GetPlayerCopy(GetOwnerID());
    return player->GetEmpireSkillTree().Warehouse && player->HasEnoughFood(GetFoodCost());
}

std::shared_ptr<DistrictWindMill> DistrictWindMill::Deserialize(boost::property_tree::ptree node)
{
    auto district = std::shared_ptr<DistrictWindMill>{ new DistrictWindMill(node.get<int>("<xmlattr>.O")) };
    district->m_health = node.get<int>("<xmlattr>.H");

    return district;
}
