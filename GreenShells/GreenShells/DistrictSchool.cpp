#include "GameSession.h"
#include <iostream>
#include "DistrictSchool.h"
#include "Player.h"

const char* DistrictSchool::NAME = "School";

DistrictSchool::DistrictSchool(int owner)
    : District<DistrictSchool>(owner, HEALTH, ATTACK_DAMAGE, FOOD_COST, FOOD_BONUS, SCIENCE_BONUS, WEAPON_BONUS)
{
}

DistrictBase* DistrictSchool::Clone()
{
    return new DistrictSchool{ *this };
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

void DistrictSchool::Repair(int repairValue)
{
    m_health = std::min(m_health + repairValue, HEALTH);
}

bool DistrictSchool::CanUpgrade()
{
    Player* player = GameSession::GetInstance().GetWorldState()->GetPlayerCopy(GameSession::GetInstance().GetCurrentPlayerID());
    return player->GetUtilitySkillTree().University;
}

int DistrictSchool::GetMaxHealth()
{
    return HEALTH;
}

const char * DistrictSchool::GetName()
{
    return NAME;
}

int DistrictSchool::GetTypeAsInt()
{
    return DISTRICT_TYPE;
}

DistrictSchool * DistrictSchool::Deserialize(boost::property_tree::ptree node)
{
    DistrictSchool* school = new DistrictSchool(node.get<int>("<xmlattr>.O"));
    school->m_health = node.get<int>("<xmlattr>.H");

    return school;
}


