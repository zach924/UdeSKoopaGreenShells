#include "UnitCannon.h"
#include <algorithm>
#include <iostream>
#include "GameSession.h"
#include "Player.h"

const char* UnitCannon::UNIT_NAME = "Cannon";

UnitCannon::UnitCannon(int owner)
    : Unit<UnitCannon>(owner, HEALTH, ACTION_POINTS, ATTACK_RANGE, ATTACK_DAMAGE, VIEW_RANGE)
{
    auto player = GameSession::GetInstance().GetWorldState()->GetPlayerCopy(m_ownerID);
    if (player->GetUtilitySkillTree().MovementUpgrade)
    {
        m_actionPointsLeft += 1;
    }
}

UnitCannon::~UnitCannon()
{
}

UnitBase* UnitCannon::Clone()
{
    return new UnitCannon{ *this };
}

void UnitCannon::LoadTexture()
{
    try
    {
        m_Texture.LoadFromFile("..\\Sprite\\Units\\64x64\\cannon.bmp");
    }
    catch (std::exception e)
    {
        std::string msg{ e.what() };
        std::cout << msg << std::endl;
    }
}

bool UnitCannon::CanUpgrade()
{
    return false;
}

int UnitCannon::GetMaxHealth()
{
    return HEALTH;
}

const char * UnitCannon::GetName()
{
    return UNIT_NAME;
}

int UnitCannon::GetTypeAsInt()
{
    return UNIT_TYPE;
}

int UnitCannon::GetViewRange()
{
    return VIEW_RANGE;
}

int UnitCannon::GetUnitTier()
{
    return UNIT_TIER;
}

void UnitCannon::Heal(int health)
{
    m_health = std::min(m_health + health, HEALTH);
}

void UnitCannon::NotifyNewTurn(int turn)
{
    m_actionPointsLeft = ACTION_POINTS;
    auto player = GameSession::GetInstance().GetWorldState()->GetPlayerCopy(m_ownerID);
    if (player->GetUtilitySkillTree().MovementUpgrade)
    {
        m_actionPointsLeft += 1;
    }
}


UnitCannon * UnitCannon::Deserialize(boost::property_tree::ptree node)
{
    UnitCannon* cannon = new UnitCannon(node.get<int>("<xmlattr>.O"));
    cannon->m_health = node.get<int>("<xmlattr>.H");
    cannon->m_actionPointsLeft = node.get<int>("<xmlattr>.APL");

    return cannon;
}
