#include "UnitSwordsmanII.h"
#include <iostream>
#include "GameSession.h"
#include "Player.h"

const char* UnitSwordsmanII::UNIT_NAME = "Swordsman MK2";

UnitSwordsmanII::UnitSwordsmanII(int owner)
    : Unit<UnitSwordsmanII>(owner, HEALTH, ACTION_POINTS, MELEE_ATTACK_RANGE, ATTACK_DAMAGE, VIEW_RANGE, WEAPON_COST)
{
    auto player = GameSession::GetInstance().GetWorldState()->GetPlayerCopy(m_ownerID);
    if (player->GetUtilitySkillTree().MovementUpgrade)
    {
        m_actionPointsLeft += 1;
    }
}

UnitSwordsmanII::~UnitSwordsmanII()
{
}

UnitBase* UnitSwordsmanII::Clone()
{
    return new UnitSwordsmanII{ *this };
}

void UnitSwordsmanII::LoadTexture()
{
    try
    {
        m_Texture.LoadFromFile("..\\Sprite\\Units\\64x64\\sword2.bmp");
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
    auto player = GameSession::GetInstance().GetWorldState()->GetPlayerCopy(m_ownerID);
    if (player->GetUtilitySkillTree().MovementUpgrade)
    {
        m_actionPointsLeft += 1;
    }
}


// NEED TO PUT THIS IN EVERY MELEE UNIT, SO THEY CAN REECEIVE DAMAGE WHEN ATTACKING
AttackNotification UnitSwordsmanII::Attack(UnitBase * target)
{
    UseActionPoints(ACTION_POINTS);
    AttackNotification targetNotification = UnitBase::Attack(target);
    AttackNotification attackerNotification = ReceiveDamage(targetNotification.RiposteDamage);

    targetNotification.AttackerIsDead = attackerNotification.TargetIsDead;
    targetNotification.CanMove = true;

    return targetNotification;
}

AttackNotification UnitSwordsmanII::Attack(DistrictBase * target)
{
    UseActionPoints(ACTION_POINTS);
    AttackNotification targetNotification = UnitBase::Attack(target);
    AttackNotification attackerNotification = ReceiveDamage(targetNotification.RiposteDamage);

    targetNotification.AttackerIsDead = attackerNotification.TargetIsDead;
    targetNotification.CanMove = true;

    return targetNotification;
}

UnitSwordsmanII * UnitSwordsmanII::Deserialize(boost::property_tree::ptree node)
{
    UnitSwordsmanII* swordsman = new UnitSwordsmanII(node.get<int>("<xmlattr>.O"));
    swordsman->m_health = node.get<int>("<xmlattr>.H");
    swordsman->m_actionPointsLeft = node.get<int>("<xmlattr>.APL");

    return swordsman;
}