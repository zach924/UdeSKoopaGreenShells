#include "GameSession.h"
#include <iostream>
#include "DistrictBlacksmith.h"
#include "Player.h"

const char* DistrictBlacksmith::NAME = "Blacksmith";

DistrictBlacksmith::DistrictBlacksmith(int owner)
    : District<DistrictBlacksmith>(owner, HEALTH, ATTACK_DAMAGE, FOOD_COST, FOOD_YIELD, SCIENCE_YIELD, WEAPON_YIELD)
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

void DistrictBlacksmith::Repair(int repairValue)
{
    m_health = std::min(m_health + repairValue, HEALTH);
}

bool DistrictBlacksmith::CanUpgrade()
{
    auto player = GameSession::GetInstance().GetWorldState()->GetPlayerCopy(GameSession::GetInstance().GetCurrentPlayerID());
    return player->GetEmpireSkillTree().Stable;
}

int DistrictBlacksmith::GetMaxHealth()
{
    return HEALTH;
}

const char * DistrictBlacksmith::GetName()
{
    return NAME;
}

int DistrictBlacksmith::GetTypeAsInt()
{
    return DISTRICT_TYPE;
}

std::shared_ptr<DistrictBlacksmith> DistrictBlacksmith::Deserialize(boost::property_tree::ptree node)
{
    auto district = std::shared_ptr<DistrictBlacksmith>{ new DistrictBlacksmith(node.get<int>("<xmlattr>.O")) };
    district->m_health = node.get<int>("<xmlattr>.H");

    return district;
}

int DistrictBlacksmith::GetViewRange()
{
    return VIEW_RANGE;
}
