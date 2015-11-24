#include "GameSession.h"
#include <iostream>
#include "DistrictFort.h"
#include "Player.h"

const char* DistrictFort::NAME = "Fort";

DistrictFort::DistrictFort(int owner)
    : District<DistrictFort>(owner, HEALTH, ATTACK_DAMAGE, FOOD_COST, FOOD_BONUS, SCIENCE_BONUS, WEAPON_BONUS)
{
}

std::shared_ptr<DistrictBase> DistrictFort::Clone()
{
    return std::shared_ptr<DistrictBase> { new DistrictFort{ *this } };
}

void DistrictFort::LoadTexture()
{
    try
    {
        m_Texture.LoadFromFile("..\\Sprite\\Districts\\64x64\\fort.bmp");
    }
    catch (std::exception e)
    {
        std::string msg{ e.what() };
        std::cout << msg << std::endl;
    }
}

DistrictFort::~DistrictFort()
{
}

void DistrictFort::Repair(int repairValue)
{
    m_health = std::min(m_health + repairValue, HEALTH);
}

bool DistrictFort::CanUpgrade()
{
    auto player = GameSession::GetInstance().GetWorldState()->GetPlayerCopy(GameSession::GetInstance().GetCurrentPlayerID());
    return player->GetArmySkillTree().Fortress;
}

int DistrictFort::GetMaxHealth()
{
    return HEALTH;
}

const char * DistrictFort::GetName()
{
    return NAME;
}

int DistrictFort::GetTypeAsInt()
{
    return DISTRICT_TYPE;
}

int DistrictFort::GetViewRange()
{
    return VIEW_RANGE;
}

std::shared_ptr<DistrictFort> DistrictFort::Deserialize(boost::property_tree::ptree node)
{
    auto district = std::shared_ptr<DistrictFort>{ new DistrictFort(node.get<int>("<xmlattr>.O")) };
    district->m_health = node.get<int>("<xmlattr>.H");

    return district;
}

