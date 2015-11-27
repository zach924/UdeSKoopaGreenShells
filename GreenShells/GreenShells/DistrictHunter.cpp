#include "GameSession.h"
#include <iostream>
#include "DistrictHunter.h"
#include "Player.h"

const char* DistrictHunter::NAME = "Hunter";

DistrictHunter::DistrictHunter(int owner)
    : District<DistrictHunter>(owner, HEALTH, ATTACK_DAMAGE, FOOD_COST, FOOD_YIELD, SCIENCE_YIELD, WEAPON_YIELD)
{
}

DistrictBase* DistrictHunter::Clone()
{
    return new DistrictHunter{ *this };
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

void DistrictHunter::Repair(int repairValue)
{
    m_health = std::min(m_health + repairValue, HEALTH);
}

bool DistrictHunter::CanUpgrade()
{
    auto player = GameSession::GetInstance().GetWorldState()->GetPlayerCopy(GameSession::GetInstance().GetCurrentPlayerID());
    return player->GetEmpireSkillTree().Farm;
}

int DistrictHunter::GetMaxHealth()
{
    return HEALTH;
}

const char * DistrictHunter::GetName()
{
    return NAME;
}

int DistrictHunter::GetTypeAsInt()
{
    return DISTRICT_TYPE;
}

int DistrictHunter::GetViewRange()
{
    return VIEW_RANGE;
}

DistrictHunter * DistrictHunter::Deserialize(boost::property_tree::ptree node)
{
    DistrictHunter* hunter = new DistrictHunter(node.get<int>("<xmlattr>.O"));
    hunter->m_health = node.get<int>("<xmlattr>.H");

    return hunter;
}
