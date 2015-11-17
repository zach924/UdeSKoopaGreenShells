#include "GameSession.h"
#include <iostream>
#include "DistrictMonastery.h"
#include "Player.h"

const char* DistrictMonastery::NAME = "Monastery";

DistrictMonastery::DistrictMonastery(int owner)
    : District<DistrictMonastery>(owner, HEALTH, ATTACK_DAMAGE, FOOD_COST, FOOD_BONUS, SCIENCE_BONUS, WEAPON_BONUS)
{
}

DistrictBase* DistrictMonastery::Clone()
{
    return new DistrictMonastery{ *this };
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
    Player* player = GameSession::GetInstance().GetWorldState()->GetPlayerCopy(GameSession::GetInstance().GetCurrentPlayerID());
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

DistrictMonastery * DistrictMonastery::Deserialize(boost::property_tree::ptree node)
{
    DistrictMonastery* monas = new DistrictMonastery(node.get<int>("<xmlattr>.O"));
    monas->m_health = node.get<int>("<xmlattr>.H");

    return monas;
}

