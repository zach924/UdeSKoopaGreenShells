#include "UnitSettler.h"
#include "GameSession.h"
#include "Player.h"
#include <iostream>

const char* UnitSettler::UNIT_NAME = "Settler";

UnitSettler::UnitSettler(int owner)
    : Unit<UnitSettler>(owner, HEALTH, ACTION_POINTS, MELEE_ATTACK_RANGE, ATTACK_DAMAGE, VIEW_RANGE, WEAPON_COST, FOOD_COST)
{
    auto player = GameSession::GetInstance().GetWorldState()->GetPlayerCopy(m_ownerID);
    if (player->GetUtilitySkillTree().MovementUpgrade)
    {
        m_actionPointsLeft += 1;
    }
}

UnitSettler::~UnitSettler()
{
}

UnitBase* UnitSettler::Clone()
{
    return new UnitSettler{ *this };
}

void UnitSettler::LoadTexture()
{
    try
    {
        m_Texture.LoadFromFile("..\\Sprite\\Units\\64x64\\settler.bmp");
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
    auto player = GameSession::GetInstance().GetWorldState()->GetPlayerCopy(m_ownerID);
    if (player->GetUtilitySkillTree().MovementUpgrade)
    {
        m_actionPointsLeft += 1;
    }
}


// NEED TO PUT THIS IN EVERY MELEE UNIT, SO THEY CAN REECEIVE DAMAGE WHEN ATTACKING
AttackNotification UnitSettler::Attack(UnitBase * target)
{
    UseActionPoints(ACTION_POINTS);
    AttackNotification targetNotification = UnitBase::Attack(target);
    AttackNotification attackerNotification = ReceiveDamage(targetNotification.RiposteDamage);

    targetNotification.AttackerIsDead = attackerNotification.TargetIsDead;
    targetNotification.CanMove = true;

    return targetNotification;
}

AttackNotification UnitSettler::Attack(DistrictBase * target)
{
    UseActionPoints(ACTION_POINTS);
    AttackNotification targetNotification = UnitBase::Attack(target);
    AttackNotification attackerNotification = ReceiveDamage(targetNotification.RiposteDamage);

    targetNotification.AttackerIsDead = attackerNotification.TargetIsDead;
    targetNotification.CanMove = true;

    return targetNotification;
}

UnitSettler * UnitSettler::Deserialize(boost::property_tree::ptree node)
{
    UnitSettler* settler = new UnitSettler(node.get<int>("<xmlattr>.O"));
    settler->m_health = node.get<int>("<xmlattr>.H");
    settler->m_actionPointsLeft = node.get<int>("<xmlattr>.APL");

    return settler;
}