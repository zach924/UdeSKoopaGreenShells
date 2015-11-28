#include "UnitSettler.h"
#include "GameSession.h"
#include "ServerSession.h"
#include "Player.h"
#include <iostream>

const char* UnitSettler::UNIT_NAME = "Settler";

UnitSettler::UnitSettler(int owner, bool hasBonusActionPoint)
    : Unit<UnitSettler>(owner, HEALTH, ACTION_POINTS, MELEE_ATTACK_RANGE, ATTACK_DAMAGE, VIEW_RANGE)
{
    if (hasBonusActionPoint)
    {
        m_actionPointsLeft += 1;
    }
}

UnitSettler::~UnitSettler()
{
}

std::shared_ptr<UnitBase> UnitSettler::Clone()
{
    return std::shared_ptr<UnitBase> { new UnitSettler{ *this } };
}

void UnitSettler::LoadTexture()
{
    try
    {
        m_unitTexture.LoadFromFile("..\\Sprite\\Units\\64x64\\settler.bmp");
    }
    catch (std::exception e)
    {
        std::string msg{ e.what() };
        std::cout << msg << std::endl;
    }
}

bool UnitSettler::CanUpgrade()
{
    return true;
}

int UnitSettler::GetMaxHealth()
{
    return HEALTH;
}

const char * UnitSettler::GetName()
{
    return UNIT_NAME;
}

int UnitSettler::GetTypeAsInt()
{
    return UNIT_TYPE;
}

int UnitSettler::GetViewRange()
{
    return VIEW_RANGE;
}

void UnitSettler::Heal(int health)
{
    m_health = std::min(m_health + health, HEALTH);
}

void UnitSettler::NotifyNewTurn(int turn)
{
    m_actionPointsLeft = ACTION_POINTS;
    auto player = ServerSession::GetInstance().GetWorldState()->GetPlayerCopy(m_ownerID);
    if (player->GetUtilitySkillTree().MovementUpgrade)
    {
        m_actionPointsLeft += 1;
    }
}


// NEED TO PUT THIS IN EVERY MELEE UNIT, SO THEY CAN REECEIVE DAMAGE WHEN ATTACKING
AttackNotification UnitSettler::Attack(std::shared_ptr<UnitBase> target)
{
    UseActionPoints(m_actionPointsLeft);
    AttackNotification targetNotification = UnitBase::Attack(target);
    AttackNotification attackerNotification = ReceiveDamage(targetNotification.RiposteDamage);

    targetNotification.AttackerIsDead = attackerNotification.TargetIsDead;
    targetNotification.CanMove = true;

    return targetNotification;
}

AttackNotification UnitSettler::Attack(std::shared_ptr<DistrictBase> target)
{
    UseActionPoints(m_actionPointsLeft);
    AttackNotification targetNotification = UnitBase::Attack(target);
    AttackNotification attackerNotification = ReceiveDamage(targetNotification.RiposteDamage);

    targetNotification.AttackerIsDead = attackerNotification.TargetIsDead;
    targetNotification.CanMove = true;

    return targetNotification;
}

std::shared_ptr<UnitSettler> UnitSettler::Deserialize(boost::property_tree::ptree node)
{
    std::shared_ptr<UnitSettler> settler = std::shared_ptr<UnitSettler>{ new UnitSettler(node.get<int>("<xmlattr>.O")) };
    settler->m_health = node.get<int>("<xmlattr>.H");
    settler->m_actionPointsLeft = node.get<int>("<xmlattr>.APL");

    return settler;
}