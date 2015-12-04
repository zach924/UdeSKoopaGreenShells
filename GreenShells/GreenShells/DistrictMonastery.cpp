#include "GameSession.h"
#include <iostream>
#include "DistrictMonastery.h"
#include "Player.h"
#include "Map.h"
#include "DistrictCathedral.h"

DistrictMonastery::DistrictMonastery(int owner)
    : District<DistrictMonastery>(owner, HEALTH, ATTACK_DAMAGE, VIEW_RANGE, NAME, DISTRICT_TYPE, FOOD_COST, WEAPON_YIELD, FOOD_YIELD, SCIENCE_YIELD, UPGRADE_TYPE)
{
}

std::shared_ptr<DistrictBase> DistrictMonastery::Clone()
{
    return std::shared_ptr<DistrictBase> { new DistrictMonastery{ *this } };
}

void DistrictMonastery::LoadTexture()
{
    try
    {
        m_Texture.LoadFromFile("Resources\\Sprite\\Districts\\64x64\\monastery.bmp");
    }
    catch (std::exception e)
    {
        std::string msg{ e.what() };
        std::cout << msg << std::endl;
    }
}

DistrictMonastery::~DistrictMonastery()
{
}

bool DistrictMonastery::CanUpgrade()
{
    auto player = GameSession::GetInstance().GetWorldState()->GetPlayerCopy(GetOwnerID());
    return player->GetEmpireSkillTree().Cathedral && player->HasEnoughFood(GetFoodCost());
}

std::shared_ptr<DistrictMonastery> DistrictMonastery::Deserialize(boost::property_tree::ptree node)
{
    auto district = std::shared_ptr<DistrictMonastery>{ new DistrictMonastery(node.get<int>("<xmlattr>.O")) };
    district->m_health = node.get<int>("<xmlattr>.H");

    return district;
}
