#include "UnitArcherII.h"
#include <algorithm>
#include <iostream>
#include "GameSession.h"
#include "Player.h"

const char* UnitArcherII::UNIT_NAME = "Archer MK2";

UnitArcherII::UnitArcherII(int owner)
    : Unit<UnitArcherII>(owner, HEALTH, ACTION_POINTS, ATTACK_RANGE, ATTACK_DAMAGE, VIEW_RANGE)
{
    auto player = GameSession::GetInstance().GetWorldState()->GetPlayerCopy(m_ownerID);
    if (player->GetUtilitySkillTree().MovementUpgrade)
    {
        m_actionPointsLeft += 1;
    }
}

UnitArcherII::~UnitArcherII()
{
}

UnitBase* UnitArcherII::Clone()
{
    return new UnitArcherII{ *this };
}

void UnitArcherII::LoadTexture()
{
    try
    {
        m_Texture.LoadFromFile("..\\Sprite\\Units\\64x64\\bow2.bmp");
    }
    catch (std::exception e)
    {
        std::string msg{ e.what() };
        std::cout << msg << std::endl;
    }
}

bool UnitArcherII::CanUpgrade()
{
    auto player = GameSession::GetInstance().GetWorldState()->GetPlayerCopy(m_ownerID);
    return player->GetArmySkillTree().RangerT3;
}

int UnitArcherII::GetMaxHealth()
{
    return HEALTH;
}

const char * UnitArcherII::GetName()
{
    return UNIT_NAME;
}

int UnitArcherII::GetTypeAsInt()
{
    return UNIT_TYPE;
}

int UnitArcherII::GetViewRange()
{
    return VIEW_RANGE;
}

int UnitArcherII::GetUnitTier()
{
    return UNIT_TIER;
}

void UnitArcherII::Heal(int health)
{
    m_health = std::min(m_health + health, HEALTH);
}

void UnitArcherII::NotifyNewTurn(int turn)
{
    m_actionPointsLeft = ACTION_POINTS;
    auto player = GameSession::GetInstance().GetWorldState()->GetPlayerCopy(m_ownerID);
    if (player->GetUtilitySkillTree().MovementUpgrade)
    {
        m_actionPointsLeft += 1;
    }
}

UnitArcherII * UnitArcherII::Deserialize(boost::property_tree::ptree node)
{
    UnitArcherII* archer = new UnitArcherII(node.get<int>("<xmlattr>.O"));
    archer->m_health = node.get<int>("<xmlattr>.H");
    archer->m_actionPointsLeft = node.get<int>("<xmlattr>.APL");

    return archer;
}