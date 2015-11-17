#include "GameSession.h"
#include <iostream>
#include "DistrictWindMill.h"
#include "Player.h"

const char* DistrictWindMill::NAME = "Windmill";

DistrictWindMill::DistrictWindMill(int owner)
    : District<DistrictWindMill>(owner, HEALTH, ATTACK_DAMAGE, FOOD_COST, FOOD_BONUS, SCIENCE_BONUS, WEAPON_BONUS)
{
}

DistrictBase* DistrictWindMill::Clone()
{
    return new DistrictWindMill{ *this };
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
    Player* player = GameSession::GetInstance().GetWorldState()->GetPlayerCopy(GameSession::GetInstance().GetCurrentPlayerID());
    return player->GetEmpireSkillTree().Warehouse;
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

DistrictWindMill * DistrictWindMill::Deserialize(boost::property_tree::ptree node)
{
    DistrictWindMill* windmill = new DistrictWindMill(node.get<int>("<xmlattr>.O"));
    windmill->m_health = node.get<int>("<xmlattr>.H");

    return windmill;
}
