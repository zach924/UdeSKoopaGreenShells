#include "GameSession.h"
#include <iostream>
#include "DistrictFishery.h"
#include "Player.h"

const char* DistrictFishery::NAME = "Fishery";

DistrictFishery::DistrictFishery(int owner)
    : District<DistrictFishery>(owner, HEALTH, ATTACK_DAMAGE, FOOD_COST, FOOD_YIELD, SCIENCE_YIELD, WEAPON_YIELD)
{
}

std::shared_ptr<DistrictBase> DistrictFishery::Clone()
{
    return std::shared_ptr<DistrictBase> { new DistrictFishery{ *this } };
}

void DistrictFishery::LoadTexture()
{
    try
    {
        m_Texture.LoadFromFile("..\\Sprite\\Districts\\64x64\\fishery.bmp");
    }
    catch (std::exception e)
    {
        std::string msg{ e.what() };
        std::cout << msg << std::endl;
    }
}

DistrictFishery::~DistrictFishery()
{
}

void DistrictFishery::Repair(int repairValue)
{
    m_health = std::min(m_health + repairValue, HEALTH);
}

bool DistrictFishery::CanUpgrade()
{
    auto player = GameSession::GetInstance().GetWorldState()->GetPlayerCopy(GameSession::GetInstance().GetCurrentPlayerID());
    return player->GetArmySkillTree().Fortress;
}

int DistrictFishery::GetMaxHealth()
{
    return HEALTH;
}

const char * DistrictFishery::GetName()
{
    return NAME;
}

int DistrictFishery::GetTypeAsInt()
{
    return DISTRICT_TYPE;
}

int DistrictFishery::GetViewRange()
{
    return VIEW_RANGE;
}

std::shared_ptr<DistrictFishery> DistrictFishery::Deserialize(boost::property_tree::ptree node)
{
    auto district = std::shared_ptr<DistrictFishery>{ new DistrictFishery(node.get<int>("<xmlattr>.O")) };
    district->m_health = node.get<int>("<xmlattr>.H");

    return district;
}

