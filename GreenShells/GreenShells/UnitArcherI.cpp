#include "UnitArcherI.h"
#include <algorithm>
#include <iostream>
#include "GameSession.h"
#include "Player.h"

const char* UnitArcherI::UNIT_NAME = "Archer MK1";

UnitArcherI::UnitArcherI(int owner)
    : Unit<UnitArcherI>(owner, HEALTH, ACTION_POINTS, ATTACK_RANGE, ATTACK_DAMAGE, VIEW_RANGE)
{
    auto player = GameSession::GetInstance().GetWorldState()->GetPlayerCopy(m_ownerID);
    if (player->GetUtilitySkillTree().MovementUpgrade)
    {
        m_actionPointsLeft += 1;
    }
}

UnitArcherI::~UnitArcherI()
{
}

UnitBase* UnitArcherI::Clone()
{
    return new UnitArcherI{ *this };
}

void UnitArcherI::LoadTexture()
{
    try
    {
        m_Texture.LoadFromFile("..\\Sprite\\Units\\64x64\\bow.bmp");
    }
    catch (std::exception e)
    {
        std::string msg{ e.what() };
        std::cout << msg << std::endl;
    }
}

bool UnitArcherI::CanUpgrade()
{
    auto player = GameSession::GetInstance().GetWorldState()->GetPlayerCopy(m_ownerID);
    return player->GetArmySkillTree().RangerT2;
}

int UnitArcherI::GetMaxHealth()
{
    return HEALTH;
}

const char * UnitArcherI::GetName()
{
    return UNIT_NAME;
}

int UnitArcherI::GetTypeAsInt()
{
    return UNIT_TYPE;
}

int UnitArcherI::GetViewRange()
{
    return VIEW_RANGE;
}

void UnitArcherI::Heal(int health)
{
    m_health = std::min(m_health + health, HEALTH);
}

void UnitArcherI::NotifyNewTurn(int turn)
{
    m_actionPointsLeft = ACTION_POINTS;
    auto player = GameSession::GetInstance().GetWorldState()->GetPlayerCopy(m_ownerID);
    if (player->GetUtilitySkillTree().MovementUpgrade)
    {
        m_actionPointsLeft += 1;
    }
}

UnitArcherI * UnitArcherI::Deserialize(boost::property_tree::ptree node)
{
    UnitArcherI* archer = new UnitArcherI(node.get<int>("<xmlattr>.O"));
    archer->m_health = node.get<int>("<xmlattr>.H");
    archer->m_actionPointsLeft = node.get<int>("<xmlattr>.APL");

    return archer;
}