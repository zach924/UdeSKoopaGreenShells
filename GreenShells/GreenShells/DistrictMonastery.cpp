#include "GameSession.h"
#include <iostream>
#include "DistrictMonastery.h"
#include "Player.h"

const char* DistrictMonastery::NAME = "Monastery";

DistrictMonastery::DistrictMonastery(int owner)
    : District<DistrictMonastery>(owner, HEALTH, ATTACK_DAMAGE, FOOD_COST, FOOD_BONUS, SCIENCE_BONUS, WEAPON_BONUS)
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
        m_Texture.LoadFromFile("..\\Sprite\\Districts\\64x64\\monastery.bmp");
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

void DistrictMonastery::Repair(int repairValue)
{
    m_health = std::min(m_health + repairValue, HEALTH);
}

bool DistrictMonastery::CanUpgrade()
{
    auto player = GameSession::GetInstance().GetWorldState()->GetPlayerCopy(GameSession::GetInstance().GetCurrentPlayerID());
    return player->GetEmpireSkillTree().Cathedral;
}

int DistrictMonastery::GetMaxHealth()
{
    return HEALTH;
}

const char * DistrictMonastery::GetName()
{
    return NAME;
}

int DistrictMonastery::GetTypeAsInt()
{
    return DISTRICT_TYPE;
}

int DistrictMonastery::GetViewRange()
{
    return VIEW_RANGE;
}

std::shared_ptr<DistrictMonastery> DistrictMonastery::Deserialize(boost::property_tree::ptree node)
{
    auto district = std::shared_ptr<DistrictMonastery>{ new DistrictMonastery(node.get<int>("<xmlattr>.O")) };
    district->m_health = node.get<int>("<xmlattr>.H");

    return district;
}
