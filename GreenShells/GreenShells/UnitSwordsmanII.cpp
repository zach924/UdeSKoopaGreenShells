#include "UnitSwordsmanII.h"
#include <iostream>
#include "GameSession.h"
#include "ServerSession.h"
#include "Player.h"

const char* UnitSwordsmanII::UNIT_NAME = "Swordsman MK2";

UnitSwordsmanII::UnitSwordsmanII(int owner, bool hasBonusActionPoint)
    : Unit<UnitSwordsmanII>(owner, HEALTH, ACTION_POINTS, MELEE_ATTACK_RANGE, ATTACK_DAMAGE, VIEW_RANGE)
{
    if (hasBonusActionPoint)
    {
        m_actionPointsLeft += 1;
    }
}

UnitSwordsmanII::~UnitSwordsmanII()
{
}

std::shared_ptr<UnitBase> UnitSwordsmanII::Clone()
{
    return std::shared_ptr<UnitBase> { new UnitSwordsmanII{ *this } };
}

void UnitSwordsmanII::LoadTexture()
{
    try
    {
        m_unitTexture.LoadFromFile("..\\Sprite\\Units\\64x64\\sword2.bmp");
    }
    catch (std::exception e)
    {
        std::string msg{ e.what() };
        std::cout << msg << std::endl;
    }
}

bool UnitSwordsmanII::CanUpgrade()
{
    auto player = GameSession::GetInstance().GetWorldState()->GetPlayerCopy(m_ownerID);
    return player->GetArmySkillTree().SwordT3;
}

int UnitSwordsmanII::GetMaxHealth()
{
    return HEALTH;
}

const char * UnitSwordsmanII::GetName()
{
    return UNIT_NAME;
}

int UnitSwordsmanII::GetTypeAsInt()
{
    return UNIT_TYPE;
}

int UnitSwordsmanII::GetViewRange()
{
    return VIEW_RANGE;
}

void UnitSwordsmanII::Heal(int health)
{
    m_health = std::min(m_health + health, HEALTH);
}

void UnitSwordsmanII::NotifyNewTurn(int turn)
{
    m_actionPointsLeft = ACTION_POINTS;
    auto player = ServerSession::GetInstance().GetWorldState()->GetPlayerCopy(m_ownerID);
    if (player->GetUtilitySkillTree().MovementUpgrade)
    {
        m_actionPointsLeft += 1;
    }
}


// NEED TO PUT THIS IN EVERY MELEE UNIT, SO THEY CAN REECEIVE DAMAGE WHEN ATTACKING
AttackNotification UnitSwordsmanII::Attack(std::shared_ptr<UnitBase> target)
{
    UseActionPoints(m_actionPointsLeft);
    AttackNotification targetNotification = UnitBase::Attack(target);
    AttackNotification attackerNotification = ReceiveDamage(targetNotification.RiposteDamage);

    targetNotification.AttackerIsDead = attackerNotification.TargetIsDead;
    targetNotification.CanMove = true;

    return targetNotification;
}

AttackNotification UnitSwordsmanII::Attack(std::shared_ptr<DistrictBase> target)
{
    UseActionPoints(m_actionPointsLeft);
    AttackNotification targetNotification = UnitBase::Attack(target);
    AttackNotification attackerNotification = ReceiveDamage(targetNotification.RiposteDamage);

    targetNotification.AttackerIsDead = attackerNotification.TargetIsDead;
    targetNotification.CanMove = true;

    return targetNotification;
}

std::shared_ptr<UnitSwordsmanII> UnitSwordsmanII::Deserialize(boost::property_tree::ptree node)
{
    std::shared_ptr<UnitSwordsmanII> swordsman = std::shared_ptr<UnitSwordsmanII>{ new UnitSwordsmanII(node.get<int>("<xmlattr>.O")) };
    swordsman->m_health = node.get<int>("<xmlattr>.H");
    swordsman->m_actionPointsLeft = node.get<int>("<xmlattr>.APL");

    return swordsman;
}