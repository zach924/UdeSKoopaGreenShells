#include "UnitShield.h"
#include <algorithm>
#include <iostream>
#include "GameSession.h"
#include "ServerSession.h"
#include "Player.h"

const char* UnitShield::UNIT_NAME = "Shield";

UnitShield::UnitShield(int owner)
    : Unit<UnitShield>(owner, HEALTH, ACTION_POINTS, ATTACK_RANGE, ATTACK_DAMAGE, VIEW_RANGE)
{
    auto player = ServerSession::GetInstance().GetWorldState()->GetPlayerCopy(m_ownerID);
    if (player->GetUtilitySkillTree().MovementUpgrade)
    {
        m_actionPointsLeft += 1;
    }
}

UnitShield::~UnitShield()
{
}

std::shared_ptr<UnitBase> UnitShield::Clone()
{
    return std::shared_ptr<UnitBase> { new UnitShield{ *this } };
}

void UnitShield::LoadTexture()
{
    try
    {
        m_Texture.LoadFromFile("..\\Sprite\\Units\\64x64\\shield.bmp");
    }
    catch (std::exception e)
    {
        std::string msg{ e.what() };
        std::cout << msg << std::endl;
    }
}

bool UnitShield::CanUpgrade()
{
    return false;
}

int UnitShield::GetMaxHealth()
{
    return HEALTH;
}

const char * UnitShield::GetName()
{
    return UNIT_NAME;
}

int UnitShield::GetTypeAsInt()
{
    return UNIT_TYPE;
}

int UnitShield::GetViewRange()
{
    return VIEW_RANGE;
}

void UnitShield::Heal(int health)
{
    m_health = std::min(m_health + health, HEALTH);
}

void UnitShield::NotifyNewTurn(int turn)
{
    m_actionPointsLeft = ACTION_POINTS;
    auto player = ServerSession::GetInstance().GetWorldState()->GetPlayerCopy(m_ownerID);
    if (player->GetUtilitySkillTree().MovementUpgrade)
    {
        m_actionPointsLeft += 1;
    }
}


std::shared_ptr<UnitShield> UnitShield::Deserialize(boost::property_tree::ptree node)
{
    std::shared_ptr<UnitShield> shield = std::shared_ptr<UnitShield>{ new UnitShield(node.get<int>("<xmlattr>.O")) };
    shield->m_health = node.get<int>("<xmlattr>.H");
    shield->m_actionPointsLeft = node.get<int>("<xmlattr>.APL");

    return shield;
}

AttackNotification UnitShield::Attack(std::shared_ptr<UnitBase> target)
{
    UseActionPoints(ACTION_POINTS);
    AttackNotification targetNotification = UnitBase::Attack(target);
    AttackNotification attackerNotification = ReceiveDamage(targetNotification.RiposteDamage);

    targetNotification.AttackerIsDead = attackerNotification.TargetIsDead;
    targetNotification.CanMove = true;

    return targetNotification;
}

AttackNotification UnitShield::Attack(std::shared_ptr<DistrictBase> target)
{
    UseActionPoints(ACTION_POINTS);
    AttackNotification targetNotification = UnitBase::Attack(target);
    AttackNotification attackerNotification = ReceiveDamage(targetNotification.RiposteDamage);

    targetNotification.AttackerIsDead = attackerNotification.TargetIsDead;
    targetNotification.CanMove = true;

    return targetNotification;
}