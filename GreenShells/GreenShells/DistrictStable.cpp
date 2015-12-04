#include "GameSession.h"
#include <iostream>
#include "DistrictStable.h"
#include "Player.h"
#include "Map.h"
#include "DistrictFort.h"

DistrictStable::DistrictStable(int owner)
    : District<DistrictStable>(owner, HEALTH, ATTACK_DAMAGE, VIEW_RANGE, NAME, DISTRICT_TYPE, FOOD_COST, WEAPON_YIELD, FOOD_YIELD, SCIENCE_YIELD, UPGRADE_TYPE)
{
}

std::shared_ptr<DistrictBase> DistrictStable::Clone()
{
    return std::shared_ptr<DistrictBase> { new DistrictStable{ *this } };
}

void DistrictStable::LoadTexture()
{
    try
    {
        m_Texture.LoadFromFile("Ressources\\Sprite\\Districts\\64x64\\stables.bmp");
    }
    catch (std::exception e)
    {
        std::string msg{ e.what() };
        std::cout << msg << std::endl;
    }
}

DistrictStable::~DistrictStable()
{
}

bool DistrictStable::CanUpgrade()
{
    auto player = GameSession::GetInstance().GetWorldState()->GetPlayerCopy(GetOwnerID());
    return player->GetEmpireSkillTree().Fort && player->HasEnoughFood(GetFoodCost());
}

std::shared_ptr<DistrictStable> DistrictStable::Deserialize(boost::property_tree::ptree node)
{
    auto district = std::shared_ptr<DistrictStable>{ new DistrictStable(node.get<int>("<xmlattr>.O")) };
    district->m_health = node.get<int>("<xmlattr>.H");

    return district;
}

