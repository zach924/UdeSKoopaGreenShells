#include "UnitSwordsmanIII.h"
#include <iostream>
#include "GameSession.h"
#include "ServerSession.h"
#include "Player.h"

const char* UnitSwordsmanIII::UNIT_NAME = "Swordsman MK3";

UnitSwordsmanIII::UnitSwordsmanIII(int owner)
    : Unit<UnitSwordsmanIII>(owner, HEALTH, ACTION_POINTS, MELEE_ATTACK_RANGE, ATTACK_DAMAGE, VIEW_RANGE)
{
    auto player = ServerSession::GetInstance().GetWorldState()->GetPlayerCopy(m_ownerID);
    if (player->GetUtilitySkillTree().MovementUpgrade)
    {
        m_actionPointsLeft += 1;
    }
}

UnitSwordsmanIII::~UnitSwordsmanIII()
{
}

std::shared_ptr<UnitBase> UnitSwordsmanIII::Clone()
{
    return std::shared_ptr<UnitBase> { new UnitSwordsmanIII{ *this } };
}

void UnitSwordsmanIII::LoadTexture()
{
    try
    {
        m_Texture.LoadFromFile("..\\Sprite\\Units\\64x64\\sword3.bmp");
    }
    catch (std::exception e)
    {
        std::string msg{ e.what() };
        std::cout << msg << std::endl;
    }
}

bool UnitSwordsmanIII::CanUpgrade()
{
    return false;
}

int UnitSwordsmanIII::GetMaxHealth()
{
    return HEALTH;
}

const char * UnitSwordsmanIII::GetName()
{
    return UNIT_NAME;
}

int UnitSwordsmanIII::GetTypeAsInt()
{
    return UNIT_TYPE;
}

int UnitSwordsmanIII::GetViewRange()
{
    return VIEW_RANGE;
}

void UnitSwordsmanIII::Heal(int health)
{
    m_health = std::min(m_health + health, HEALTH);
}

void UnitSwordsmanIII::NotifyNewTurn(int turn)
{
    m_actionPointsLeft = ACTION_POINTS;
    auto player = ServerSession::GetInstance().GetWorldState()->GetPlayerCopy(m_ownerID);
    if (player->GetUtilitySkillTree().MovementUpgrade)
    {
        m_actionPointsLeft += 1;
    }
}


// NEED TO PUT THIS IN EVERY MELEE UNIT, SO THEY CAN REECEIVE DAMAGE WHEN ATTACKING
AttackNotification UnitSwordsmanIII::Attack(std::shared_ptr<UnitBase> target)
{
    UseActionPoints(ACTION_POINTS);
    AttackNotification targetNotification = UnitBase::Attack(target);
    AttackNotification attackerNotification = ReceiveDamage(targetNotification.RiposteDamage);

    targetNotification.AttackerIsDead = attackerNotification.TargetIsDead;
    targetNotification.CanMove = true;

    return targetNotification;
}

AttackNotification UnitSwordsmanIII::Attack(std::shared_ptr<DistrictBase> target)
{
    UseActionPoints(ACTION_POINTS);
    AttackNotification targetNotification = UnitBase::Attack(target);
    AttackNotification attackerNotification = ReceiveDamage(targetNotification.RiposteDamage);

    targetNotification.AttackerIsDead = attackerNotification.TargetIsDead;
    targetNotification.CanMove = true;

    return targetNotification;
}

std::shared_ptr<UnitSwordsmanIII> UnitSwordsmanIII::Deserialize(boost::property_tree::ptree node)
{
    std::shared_ptr<UnitSwordsmanIII> swordsman = std::shared_ptr<UnitSwordsmanIII>{ new UnitSwordsmanIII(node.get<int>("<xmlattr>.O")) };
    swordsman->m_health = node.get<int>("<xmlattr>.H");
    swordsman->m_actionPointsLeft = node.get<int>("<xmlattr>.APL");

    return swordsman;
}


