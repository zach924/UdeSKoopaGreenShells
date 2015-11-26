#include "UnitBuilder.h"
#include <algorithm>
#include <iostream>
#include "GameSession.h"
#include "ServerSession.h"
#include "Player.h"

const char* UnitBuilder::UNIT_NAME = "Builder";

UnitBuilder::UnitBuilder(int owner)
    : Unit<UnitBuilder>(owner, HEALTH, ACTION_POINTS, ATTACK_RANGE, ATTACK_DAMAGE, VIEW_RANGE)
{
    auto player = ServerSession::GetInstance().GetWorldState()->GetPlayerCopy(m_ownerID);
    if (player->GetUtilitySkillTree().MovementUpgrade)
    {
        m_actionPointsLeft += 1;
    }
}

UnitBuilder::~UnitBuilder()
{
}

std::shared_ptr<UnitBase> UnitBuilder::Clone()
{
    return std::shared_ptr<UnitBase> { new UnitBuilder{ *this } };
}

void UnitBuilder::LoadTexture()
{
    try
    {
        m_Texture.LoadFromFile("..\\Sprite\\Units\\64x64\\builder.bmp");
    }
    catch (std::exception e)
    {
        std::string msg{ e.what() };
        std::cout << msg << std::endl;
    }
}

bool UnitBuilder::CanUpgrade()
{
    return true;
}

int UnitBuilder::GetMaxHealth()
{
    return HEALTH;
}

const char * UnitBuilder::GetName()
{
    return UNIT_NAME;
}

int UnitBuilder::GetTypeAsInt()
{
    return UNIT_TYPE;
}

int UnitBuilder::GetViewRange()
{
    return VIEW_RANGE;
}

void UnitBuilder::Heal(int health)
{
    m_health = std::min(m_health + health, HEALTH);
}

void UnitBuilder::NotifyNewTurn(int turn)
{
    m_actionPointsLeft = ACTION_POINTS;
    auto player = ServerSession::GetInstance().GetWorldState()->GetPlayerCopy(m_ownerID);
    if (player->GetUtilitySkillTree().MovementUpgrade)
    {
        m_actionPointsLeft += 1;
    }
}


std::shared_ptr<UnitBuilder> UnitBuilder::Deserialize(boost::property_tree::ptree node)
{
    std::shared_ptr<UnitBuilder> militia = std::shared_ptr<UnitBuilder>{ new UnitBuilder(node.get<int>("<xmlattr>.O")) };
    militia->m_health = node.get<int>("<xmlattr>.H");
    militia->m_actionPointsLeft = node.get<int>("<xmlattr>.APL");

    return militia;
}

