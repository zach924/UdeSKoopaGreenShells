#include "GameSession.h"
#include <iostream>
#include "DistrictStable.h"
#include "Player.h"

const char* DistrictStable::NAME = "Stable";

DistrictStable::DistrictStable(int owner)
    : District<DistrictStable>(owner, HEALTH, ATTACK_DAMAGE, FOOD_COST, FOOD_BONUS, SCIENCE_BONUS, WEAPON_BONUS)
{
}

std::shared_ptr<DistrictBase> DistrictStable::Clone()
{
    return std::shared_ptr<DistrictBase> { new DistrictStable{ *this } };
}

void DistrictStable::LoadTexture()
{
    try
    {
        m_Texture.LoadFromFile("..\\Sprite\\Districts\\64x64\\stables.bmp");
    }
    catch (std::exception e)
    {
        std::string msg{ e.what() };
        std::cout << msg << std::endl;
    }
}

DistrictStable::~DistrictStable()
{
}

void DistrictStable::Repair(int repairValue)
{
    m_health = std::min(m_health + repairValue, HEALTH);
}

bool DistrictStable::CanUpgrade()
{
    auto player = GameSession::GetInstance().GetWorldState()->GetPlayerCopy(GameSession::GetInstance().GetCurrentPlayerID());
    return player->GetEmpireSkillTree().Fort;
}

int DistrictStable::GetMaxHealth()
{
    return HEALTH;
}

const char * DistrictStable::GetName()
{
    return NAME;
}

int DistrictStable::GetTypeAsInt()
{
    return DISTRICT_TYPE;
}

int DistrictStable::GetViewRange()
{
    return VIEW_RANGE;
}

std::shared_ptr<DistrictStable> DistrictStable::Deserialize(boost::property_tree::ptree node)
{
    auto district = std::shared_ptr<DistrictStable>{ new DistrictStable(node.get<int>("<xmlattr>.O")) };
    district->m_health = node.get<int>("<xmlattr>.H");

    return district;
}

