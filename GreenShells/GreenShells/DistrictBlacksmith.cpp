#include "GameSession.h"
#include <iostream>
#include "DistrictBlacksmith.h"
#include "Player.h"

const char* DistrictBlacksmith::NAME = "Blacksmith";

DistrictBlacksmith::DistrictBlacksmith(int owner)
    : District<DistrictBlacksmith>(owner, HEALTH, ATTACK_DAMAGE, FOOD_COST, FOOD_BONUS, SCIENCE_BONUS, WEAPON_BONUS)
{
}

DistrictBase* DistrictBlacksmith::Clone()
{
    return new DistrictBlacksmith{ *this };
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
    Player* player = GameSession::GetInstance().GetWorldState()->GetPlayerCopy(GameSession::GetInstance().GetCurrentPlayerID());
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

DistrictBlacksmith * DistrictBlacksmith::Deserialize(boost::property_tree::ptree node)
{
    DistrictBlacksmith* blacksmith = new DistrictBlacksmith(node.get<int>("<xmlattr>.O"));
    blacksmith->m_health = node.get<int>("<xmlattr>.H");

    return blacksmith;
}
