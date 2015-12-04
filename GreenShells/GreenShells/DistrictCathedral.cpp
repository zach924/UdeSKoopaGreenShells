#include "GameSession.h"
#include <iostream>
#include "DistrictCathedral.h"
#include "Player.h"
#include "Map.h"
#include "DistrictSchool.h"

DistrictCathedral::DistrictCathedral(int owner)
    : District<DistrictCathedral>(owner, HEALTH, ATTACK_DAMAGE, VIEW_RANGE, NAME, DISTRICT_TYPE, FOOD_COST, WEAPON_YIELD, FOOD_YIELD, SCIENCE_YIELD, UPGRADE_TYPE)
{
}

std::shared_ptr<DistrictBase> DistrictCathedral::Clone()
{
    return std::shared_ptr<DistrictBase> { new DistrictCathedral{ *this }};
}

void DistrictCathedral::LoadTexture()
{
    try
    {
        m_Texture.LoadFromFile("Ressources\\Sprite\\Districts\\64x64\\cathedral.bmp");
    }
    catch (std::exception e)
    {
        std::string msg{ e.what() };
        std::cout << msg << std::endl;
    }
}

bool DistrictCathedral::CanUpgrade()
{
    auto player = GameSession::GetInstance().GetWorldState()->GetPlayerCopy(GetOwnerID());
    return player->GetEmpireSkillTree().School && player->HasEnoughFood(GetFoodCost());
}

DistrictCathedral::~DistrictCathedral()
{
}

std::shared_ptr<DistrictCathedral> DistrictCathedral::Deserialize(boost::property_tree::ptree node)
{
    auto district = std::shared_ptr<DistrictCathedral>{ new DistrictCathedral(node.get<int>("<xmlattr>.O")) };
    district->m_health = node.get<int>("<xmlattr>.H");

    return district;
}


