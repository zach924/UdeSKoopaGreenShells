#include "GameSession.h"
#include <iostream>
#include "DistrictFarm.h"
#include "Player.h"

const char* DistrictFarm::NAME = "Farm";

DistrictFarm::DistrictFarm(int owner)
    : District<DistrictFarm>(owner, HEALTH, NORMAL_DISTRICT_ATTACK_DMG, VIEW_RANGE, FOOD_COST, WEAPON_YIELD, FOOD_YIELD, SCIENCE_YIELD)
{
}

DistrictBase* DistrictFarm::Clone()
{
    return new DistrictFarm{ *this };
}

void DistrictFarm::ChangeOwner(int newOwner)
{
    DistrictBase::ChangeOwner(newOwner);
    m_health = HEALTH;
}

void DistrictFarm::LoadTexture()
{
    try
    {
        m_Texture.LoadFromFile("..\\Sprite\\Districts\\64x64\\farm.bmp");
    }
    catch (std::exception e)
    {
        std::string msg{ e.what() };
        std::cout << msg << std::endl;
    }
}

DistrictFarm::~DistrictFarm()
{
}

void DistrictFarm::Repair(int repairValue)
{
    m_health = std::min(m_health + repairValue, HEALTH);
}

bool DistrictFarm::CanUpgrade()
{
    auto player = GameSession::GetInstance().GetWorldState()->GetPlayerCopy(m_ownerID);
    return player->GetEmpireSkillTree().Windmill;
}

int DistrictFarm::GetMaxHealth()
{
    return HEALTH;
}

const char * DistrictFarm::GetName()
{
    return NAME;
}

int DistrictFarm::GetTypeAsInt()
{
    return DISTRICT_TYPE;
}

int DistrictFarm::GetViewRange()
{
    return VIEW_RANGE;
}

DistrictFarm * DistrictFarm::Deserialize(boost::property_tree::ptree node)
{
    DistrictFarm* farm = new DistrictFarm(node.get<int>("<xmlattr>.O"));
    farm->m_health = node.get<int>("<xmlattr>.H");

    return farm;
}