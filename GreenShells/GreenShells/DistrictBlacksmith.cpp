#include "GameSession.h"
#include <iostream>
#include "DistrictBlacksmith.h"
#include "Player.h"

DistrictBlacksmith::DistrictBlacksmith(int owner)
    : District<DistrictBlacksmith>(owner, HEALTH, ATTACK_DAMAGE, VIEW_RANGE, NAME, DISTRICT_TYPE, FOOD_COST, WEAPON_YIELD, FOOD_YIELD, SCIENCE_YIELD)
{
}

std::shared_ptr<DistrictBase> DistrictBlacksmith::Clone()
{
    return std::shared_ptr<DistrictBase> { new DistrictBlacksmith{ *this } };
}

void DistrictBlacksmith::LoadTexture()
{
    try
    {
        m_Texture.LoadFromFile("..\\Sprite\\Districts\\64x64\\blacksmith.bmp");
    }
    catch (std::exception e)
    {
        std::string msg{ e.what() };
        std::cout << msg << std::endl;
    }
}

DistrictBlacksmith::~DistrictBlacksmith()
{
}

bool DistrictBlacksmith::CanUpgrade()
{
    auto player = GameSession::GetInstance().GetWorldState()->GetPlayerCopy(GetOwnerID());
    return player->GetEmpireSkillTree().Stable;
}

std::shared_ptr<DistrictBlacksmith> DistrictBlacksmith::Deserialize(boost::property_tree::ptree node)
{
    auto district = std::shared_ptr<DistrictBlacksmith>{ new DistrictBlacksmith(node.get<int>("<xmlattr>.O")) };
    district->m_health = node.get<int>("<xmlattr>.H");

    return district;
}