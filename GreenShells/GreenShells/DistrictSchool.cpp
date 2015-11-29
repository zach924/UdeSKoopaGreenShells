#include "GameSession.h"
#include <iostream>
#include "DistrictSchool.h"
#include "Player.h"

DistrictSchool::DistrictSchool(int owner)
    : District<DistrictSchool>(owner, HEALTH, ATTACK_DAMAGE, VIEW_RANGE, NAME, DISTRICT_TYPE, FOOD_COST, WEAPON_YIELD, FOOD_YIELD, SCIENCE_YIELD)
{
}

std::shared_ptr<DistrictBase> DistrictSchool::Clone()
{
    return std::shared_ptr<DistrictBase> { new DistrictSchool{ *this } };
}

void DistrictSchool::LoadTexture()
{
    try
    {
        m_Texture.LoadFromFile("..\\Sprite\\Districts\\64x64\\school.bmp");
    }
    catch (std::exception e)
    {
        std::string msg{ e.what() };
        std::cout << msg << std::endl;
    }
}

DistrictSchool::~DistrictSchool()
{
}

bool DistrictSchool::CanUpgrade()
{
    auto player = GameSession::GetInstance().GetWorldState()->GetPlayerCopy(GetOwnerID());
    return player->GetUtilitySkillTree().University;
}

std::shared_ptr<DistrictSchool> DistrictSchool::Deserialize(boost::property_tree::ptree node)
{
    auto district = std::shared_ptr<DistrictSchool>{ new DistrictSchool(node.get<int>("<xmlattr>.O")) };
    district->m_health = node.get<int>("<xmlattr>.H");

    return district;
}
