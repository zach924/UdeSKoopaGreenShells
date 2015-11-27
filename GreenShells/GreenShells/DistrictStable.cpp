#include "GameSession.h"
#include <iostream>
#include "DistrictStable.h"
#include "Player.h"
#include "Map.h"
#include "DistrictFort.h"

const char* DistrictStable::NAME = "Stable";

DistrictStable::DistrictStable(int owner)
    : District<DistrictStable>(owner, HEALTH, ATTACK_DAMAGE, FOOD_COST, FOOD_BONUS, SCIENCE_BONUS, WEAPON_BONUS)
{
}

DistrictBase* DistrictStable::Clone()
{
    return new DistrictStable{ *this };
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
    return player->GetEmpireSkillTree().Fort && player->HasRessourcesForDistrict(DistrictFort::DISTRICT_TYPE);
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

void DistrictStable::Upgrade(Map * map)
{
    map->GetTile(GetPosition())->SetDistrict(new DistrictFort(GetOwnerID()));
}

DistrictStable * DistrictStable::Deserialize(boost::property_tree::ptree node)
{
    DistrictStable* stable = new DistrictStable(node.get<int>("<xmlattr>.O"));
    stable->m_health = node.get<int>("<xmlattr>.H");

    return stable;
}

