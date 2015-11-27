#include "GameSession.h"
#include <iostream>
#include "DistrictWindMill.h"
#include "Player.h"
#include "Map.h"
#include "DistrictWarehouse.h"

const char* DistrictWindMill::NAME = "Windmill";

DistrictWindMill::DistrictWindMill(int owner)
    : District<DistrictWindMill>(owner, HEALTH, ATTACK_DAMAGE, FOOD_COST, FOOD_BONUS, SCIENCE_BONUS, WEAPON_BONUS)
{
}

std::shared_ptr<DistrictBase> DistrictWindMill::Clone()
{
    return std::shared_ptr<DistrictBase> { new DistrictWindMill{ *this } };
}

void DistrictWindMill::LoadTexture()
{
    try
    {
        m_Texture.LoadFromFile("..\\Sprite\\Districts\\64x64\\windmill.bmp");
    }
    catch (std::exception e)
    {
        std::string msg{ e.what() };
        std::cout << msg << std::endl;
    }
}

DistrictWindMill::~DistrictWindMill()
{
}

void DistrictWindMill::Repair(int repairValue)
{
    m_health = std::min(m_health + repairValue, HEALTH);
}

bool DistrictWindMill::CanUpgrade()
{
    auto player = GameSession::GetInstance().GetWorldState()->GetPlayerCopy(GameSession::GetInstance().GetCurrentPlayerID());
    return player->GetEmpireSkillTree().Warehouse && player->HasRessourcesForDistrict(DistrictWarehouse::DISTRICT_TYPE);
}

int DistrictWindMill::GetMaxHealth()
{
    return HEALTH;
}

const char * DistrictWindMill::GetName()
{
    return NAME;
}

int DistrictWindMill::GetTypeAsInt()
{
    return DISTRICT_TYPE;
}

int DistrictWindMill::GetViewRange()
{
    return VIEW_RANGE;
}

void DistrictWindMill::Upgrade(Map * map)
{
    map->GetTile(GetPosition())->SetDistrict(std::shared_ptr<DistrictBase>{new DistrictWarehouse(GetOwnerID())});
}

std::shared_ptr<DistrictWindMill> DistrictWindMill::Deserialize(boost::property_tree::ptree node)
{
    auto district = std::shared_ptr<DistrictWindMill>{ new DistrictWindMill(node.get<int>("<xmlattr>.O")) };
    district->m_health = node.get<int>("<xmlattr>.H");

    return district;
}
