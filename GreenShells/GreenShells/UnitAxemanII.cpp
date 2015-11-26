#include "UnitAxemanII.h"
#include <algorithm>
#include <iostream>
#include "GameSession.h"
#include "ServerSession.h"
#include "Player.h"

const char* UnitAxemanII::UNIT_NAME = "Axeman MK2";

UnitAxemanII::UnitAxemanII(int owner)
    : Unit<UnitAxemanII>(owner, HEALTH, ACTION_POINTS, ATTACK_RANGE, ATTACK_DAMAGE, VIEW_RANGE)
{
    auto player = ServerSession::GetInstance().GetWorldState()->GetPlayerCopy(m_ownerID);
    if (player->GetUtilitySkillTree().MovementUpgrade)
    {
        m_actionPointsLeft += 1;
    }
}

UnitAxemanII::~UnitAxemanII()
{
}

std::shared_ptr<UnitBase> UnitAxemanII::Clone()
{
    return std::shared_ptr<UnitBase> { new UnitAxemanII{ *this } };
}

void UnitAxemanII::LoadTexture()
{
    try
    {
        m_Texture.LoadFromFile("..\\Sprite\\Units\\64x64\\axe2.bmp");
    }
    catch (std::exception e)
    {
        std::string msg{ e.what() };
        std::cout << msg << std::endl;
    }
}

bool UnitAxemanII::CanUpgrade()
{
    return false;
}

int UnitAxemanII::GetMaxHealth()
{
    return HEALTH;
}

const char * UnitAxemanII::GetName()
{
    return UNIT_NAME;
}

int UnitAxemanII::GetTypeAsInt()
{
    return UNIT_TYPE;
}

int UnitAxemanII::GetViewRange()
{
    return VIEW_RANGE;
}

void UnitAxemanII::Heal(int health)
{
    m_health = std::min(m_health + health, HEALTH);
}

void UnitAxemanII::NotifyNewTurn(int turn)
{
    m_actionPointsLeft = ACTION_POINTS;
    auto player = ServerSession::GetInstance().GetWorldState()->GetPlayerCopy(m_ownerID);
    if (player->GetUtilitySkillTree().MovementUpgrade)
    {
        m_actionPointsLeft += 1;
    }
}


std::shared_ptr<UnitAxemanII> UnitAxemanII::Deserialize(boost::property_tree::ptree node)
{
    std::shared_ptr<UnitAxemanII> axeman = std::shared_ptr<UnitAxemanII>{ new UnitAxemanII(node.get<int>("<xmlattr>.O")) };
    axeman->m_health = node.get<int>("<xmlattr>.H");
    axeman->m_actionPointsLeft = node.get<int>("<xmlattr>.APL");

    return axeman;
}

AttackNotification UnitAxemanII::Attack(std::shared_ptr<UnitBase> target)
{
    UseActionPoints(ACTION_POINTS);
    AttackNotification targetNotification = UnitBase::Attack(target);
    AttackNotification attackerNotification = ReceiveDamage(targetNotification.RiposteDamage);

    targetNotification.AttackerIsDead = attackerNotification.TargetIsDead;
    targetNotification.CanMove = true;

    return targetNotification;
}

AttackNotification UnitAxemanII::Attack(std::shared_ptr<DistrictBase> target)
{
    UseActionPoints(ACTION_POINTS);
    AttackNotification targetNotification = UnitBase::Attack(target);
    AttackNotification attackerNotification = ReceiveDamage(targetNotification.RiposteDamage);

    targetNotification.AttackerIsDead = attackerNotification.TargetIsDead;
    targetNotification.CanMove = true;

    return targetNotification;
}