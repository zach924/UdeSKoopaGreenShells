#include "GameSession.h"
#include <iostream>
#include "DistrictCathedral.h"
#include "Player.h"

const char* DistrictCathedral::NAME = "Cathedral";

DistrictCathedral::DistrictCathedral(int owner)
    : District<DistrictCathedral>(owner, HEALTH, ATTACK_DAMAGE, FOOD_COST, FOOD_BONUS, SCIENCE_BONUS, WEAPON_BONUS)
{
}

DistrictBase* DistrictCathedral::Clone()
{
    return new DistrictCathedral{ *this };
}

void DistrictCathedral::LoadTexture()
{
    try
    {
        m_Texture.LoadFromFile("..\\Sprite\\Districts\\64x64\\cathedral.bmp");
    }
    catch (std::exception e)
    {
        std::string msg{ e.what() };
        std::cout << msg << std::endl;
    }
}

DistrictCathedral::~DistrictCathedral()
{
}

void DistrictCathedral::Repair(int repairValue)
{
    m_health = std::min(m_health + repairValue, HEALTH);
}

bool DistrictCathedral::CanUpgrade()
{
    Player* player = GameSession::GetInstance().GetWorldState()->GetPlayerCopy(GameSession::GetInstance().GetCurrentPlayerID());
    //TODO: need schoool 
    return true;
    //return player->GetEmpireSkillTree().School;
}

int DistrictCathedral::GetMaxHealth()
{
    return HEALTH;
}

const char * DistrictCathedral::GetName()
{
    return NAME;
}

int DistrictCathedral::GetTypeAsInt()
{
    return DISTRICT_TYPE;
}

DistrictCathedral * DistrictCathedral::Deserialize(boost::property_tree::ptree node)
{
    DistrictCathedral* cath = new DistrictCathedral(node.get<int>("<xmlattr>.O"));
    cath->m_health = node.get<int>("<xmlattr>.H");

    return cath;
}


