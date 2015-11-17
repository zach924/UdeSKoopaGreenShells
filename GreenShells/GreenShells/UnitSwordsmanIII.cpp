#include "UnitSwordsmanIII.h"
#include <iostream>
#include "GameSession.h"
#include "Player.h"

const char* UnitSwordsmanIII::UNIT_NAME = "Swordsman MK3";

UnitSwordsmanIII::UnitSwordsmanIII(int owner)
    : Unit<UnitSwordsmanIII>(owner, HEALTH, ACTION_POINTS, MELEE_ATTACK_RANGE, ATTACK_DAMAGE)
{
}

UnitSwordsmanIII::~UnitSwordsmanIII()
{
}

UnitBase* UnitSwordsmanIII::Clone()
{
    return new UnitSwordsmanIII{ *this };
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

void UnitSwordsmanIII::Heal(int health)
{
    m_health = std::min(m_health + health, HEALTH);
}

void UnitSwordsmanIII::NotifyNewTurn(int turn)
{
    m_actionPointsLeft = ACTION_POINTS;
    std::shared_ptr<Player> currentPlayer{ GameSession::GetInstance().GetWorldState()->GetPlayerCopy(m_ownerID) };
    if (currentPlayer->GetUtilitySkillTree().MovementUpgrade)
    {
        m_actionPointsLeft += 1;
    }
}


// NEED TO PUT THIS IN EVERY MELEE UNIT, SO THEY CAN REECEIVE DAMAGE WHEN ATTACKING
AttackNotification UnitSwordsmanIII::Attack(UnitBase * target)
{
    UseActionPoints(ACTION_POINTS);
    AttackNotification targetNotification = UnitBase::Attack(target);
    AttackNotification attackerNotification = ReceiveDamage(targetNotification.RiposteDamage);

    targetNotification.AttackerIsDead = attackerNotification.TargetIsDead;
    targetNotification.CanMove = true;

    return targetNotification;
}

AttackNotification UnitSwordsmanIII::Attack(DistrictBase * target)
{
    UseActionPoints(ACTION_POINTS);
    AttackNotification targetNotification = UnitBase::Attack(target);
    AttackNotification attackerNotification = ReceiveDamage(targetNotification.RiposteDamage);

    targetNotification.AttackerIsDead = attackerNotification.TargetIsDead;
    targetNotification.CanMove = true;

    return targetNotification;
}

UnitSwordsmanIII * UnitSwordsmanIII::Deserialize(boost::property_tree::ptree node)
{
    UnitSwordsmanIII* swordsman = new UnitSwordsmanIII(node.get<int>("<xmlattr>.O"));
    swordsman->m_health = node.get<int>("<xmlattr>.H");
    swordsman->m_actionPointsLeft = node.get<int>("<xmlattr>.APL");

    return swordsman;
}


