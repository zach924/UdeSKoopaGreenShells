#include "GameSession.h"
#include <iostream>
#include "DistrictHunter.h"
#include "Player.h"

DistrictHunter::DistrictHunter(int owner)
    : District<DistrictHunter>(owner, HEALTH, ATTACK_DAMAGE, VIEW_RANGE, NAME, DISTRICT_TYPE, FOOD_COST, WEAPON_YIELD, FOOD_YIELD, SCIENCE_YIELD)
{
}

std::shared_ptr<DistrictBase> DistrictHunter::Clone()
{
    return std::shared_ptr<DistrictBase> { new DistrictHunter{ *this } };
}

void DistrictHunter::LoadTexture()
{
    try
    {
        m_Texture.LoadFromFile("..\\Sprite\\Districts\\64x64\\hunter.bmp");
    }
    catch (std::exception e)
    {
        std::string msg{ e.what() };
        std::cout << msg << std::endl;
    }
}

DistrictHunter::~DistrictHunter()
{
}

bool DistrictHunter::CanUpgrade()
{
    auto player = GameSession::GetInstance().GetWorldState()->GetPlayerCopy(GetOwnerID());
    return player->GetEmpireSkillTree().Farm;
}

std::shared_ptr<DistrictHunter> DistrictHunter::Deserialize(boost::property_tree::ptree node)
{
    auto district = std::shared_ptr<DistrictHunter>{ new DistrictHunter(node.get<int>("<xmlattr>.O")) };
    district->m_health = node.get<int>("<xmlattr>.H");

    return district;
}
