#include "GameSession.h"
#include <iostream>
#include "DistrictFarm.h"
#include "Player.h"
#include "Map.h"
#include "DistrictWindMill.h"

DistrictFarm::DistrictFarm(int owner)
    : District<DistrictFarm>(owner, HEALTH, ATTACK_DAMAGE, VIEW_RANGE, NAME, DISTRICT_TYPE, FOOD_COST, WEAPON_YIELD, FOOD_YIELD, SCIENCE_YIELD, UPGRADE_TYPE)
{
}

std::shared_ptr<DistrictBase> DistrictFarm::Clone()
{
    return std::shared_ptr<DistrictBase> { new DistrictFarm{ *this } };
}

void DistrictFarm::LoadTexture()
{
    try
    {
        m_Texture.LoadFromFile("Ressources\\Sprite\\Districts\\64x64\\farm.bmp");
    }
    catch (std::exception e)
    {
        std::string msg{ e.what() };
        std::cout << msg << std::endl;
    }
}

DistrictFarm::~DistrictFarm()
{
}

bool DistrictFarm::CanUpgrade()
{
    auto player = GameSession::GetInstance().GetWorldState()->GetPlayerCopy(GetOwnerID());
    return player->GetEmpireSkillTree().Windmill && player->HasEnoughFood(GetFoodCost());
}

std::shared_ptr<DistrictFarm> DistrictFarm::Deserialize(boost::property_tree::ptree node)
{
    auto farm = std::shared_ptr<DistrictFarm>{ new DistrictFarm(node.get<int>("<xmlattr>.O")) };
    farm->m_health = node.get<int>("<xmlattr>.H");

    return farm;
}