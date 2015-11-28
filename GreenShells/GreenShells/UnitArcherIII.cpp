#include "UnitArcherIII.h"
#include <algorithm>
#include <iostream>
#include "GameSession.h"
#include "ServerSession.h"
#include "Player.h"

const char* UnitArcherIII::UNIT_NAME = "Archer MK3";

UnitArcherIII::UnitArcherIII(int owner, bool hasBonusActionPoint)
    : Unit<UnitArcherIII>(owner, HEALTH, ACTION_POINTS, ATTACK_RANGE, ATTACK_DAMAGE, VIEW_RANGE)
{
    if (hasBonusActionPoint)
    {
        m_actionPointsLeft += 1;
    }
}

UnitArcherIII::~UnitArcherIII()
{
}

std::shared_ptr<UnitBase> UnitArcherIII::Clone()
{
    return std::shared_ptr<UnitBase> { new UnitArcherIII{ *this } };
}

void UnitArcherIII::LoadTexture()
{
    try
    {
        m_Texture.LoadFromFile("..\\Sprite\\Units\\64x64\\bow3.bmp");
    }
    catch (std::exception e)
    {
        std::string msg{ e.what() };
        std::cout << msg << std::endl;
    }
}

bool UnitArcherIII::CanUpgrade()
{
    return false;
}

int UnitArcherIII::GetMaxHealth()
{
    return HEALTH;
}

const char * UnitArcherIII::GetName()
{
    return UNIT_NAME;
}

int UnitArcherIII::GetTypeAsInt()
{
    return UNIT_TYPE;
}

int UnitArcherIII::GetViewRange()
{
    return VIEW_RANGE;
}

void UnitArcherIII::Heal(int health)
{
    m_health = std::min(m_health + health, HEALTH);
}

void UnitArcherIII::NotifyNewTurn(int turn)
{
    m_actionPointsLeft = ACTION_POINTS;
    auto player = ServerSession::GetInstance().GetWorldState()->GetPlayerCopy(m_ownerID);
    if (player->GetUtilitySkillTree().MovementUpgrade)
    {
        m_actionPointsLeft += 1;
    }
}


std::shared_ptr<UnitArcherIII> UnitArcherIII::Deserialize(boost::property_tree::ptree node)
{
    std::shared_ptr<UnitArcherIII> archer = std::shared_ptr<UnitArcherIII>{ new UnitArcherIII(node.get<int>("<xmlattr>.O")) };
    archer->m_health = node.get<int>("<xmlattr>.H");
    archer->m_actionPointsLeft = node.get<int>("<xmlattr>.APL");

    return archer;
}