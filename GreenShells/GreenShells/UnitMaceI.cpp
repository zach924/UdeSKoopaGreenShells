#include "UnitMaceI.h"
#include <algorithm>
#include <iostream>
#include "GameSession.h"
#include "Player.h"

const char* UnitMaceI::UNIT_NAME = "Mace MK1";

UnitMaceI::UnitMaceI(int owner)
    : Unit<UnitMaceI>(owner, HEALTH, ACTION_POINTS, ATTACK_RANGE, ATTACK_DAMAGE, VIEW_RANGE, WEAPON_COST)
{
    auto player = GameSession::GetInstance().GetWorldState()->GetPlayerCopy(m_ownerID);
    if (player->GetUtilitySkillTree().MovementUpgrade)
    {
        m_actionPointsLeft += 1;
    }
}

UnitMaceI::~UnitMaceI()
{
}

UnitBase* UnitMaceI::Clone()
{
    return new UnitMaceI{ *this };
}

void UnitMaceI::LoadTexture()
{
    try
    {
        m_Texture.LoadFromFile("..\\Sprite\\Units\\64x64\\mace.bmp");
    }
    catch (std::exception e)
    {
        std::string msg{ e.what() };
        std::cout << msg << std::endl;
    }
}

bool UnitMaceI::CanUpgrade()
{
    auto player = GameSession::GetInstance().GetWorldState()->GetPlayerCopy(m_ownerID);
    return player->GetArmySkillTree().MaceT2;
}

int UnitMaceI::GetMaxHealth()
{
    return HEALTH;
}

const char * UnitMaceI::GetName()
{
    return UNIT_NAME;
}

int UnitMaceI::GetTypeAsInt()
{
    return UNIT_TYPE;
}

int UnitMaceI::GetViewRange()
{
    return VIEW_RANGE;
}

void UnitMaceI::Heal(int health)
{
    m_health = std::min(m_health + health, HEALTH);
}

void UnitMaceI::NotifyNewTurn(int turn)
{
    m_actionPointsLeft = ACTION_POINTS;
    auto player = GameSession::GetInstance().GetWorldState()->GetPlayerCopy(m_ownerID);
    if (player->GetUtilitySkillTree().MovementUpgrade)
    {
        m_actionPointsLeft += 1;
    }
}


UnitMaceI * UnitMaceI::Deserialize(boost::property_tree::ptree node)
{
    UnitMaceI* mace = new UnitMaceI(node.get<int>("<xmlattr>.O"));
    mace->m_health = node.get<int>("<xmlattr>.H");
    mace->m_actionPointsLeft = node.get<int>("<xmlattr>.APL");

    return mace;
}

AttackNotification UnitMaceI::Attack(UnitBase * target)
{
    UseActionPoints(ACTION_POINTS);
    AttackNotification targetNotification = UnitBase::Attack(target);
    AttackNotification attackerNotification = ReceiveDamage(targetNotification.RiposteDamage);

    targetNotification.AttackerIsDead = attackerNotification.TargetIsDead;
    targetNotification.CanMove = true;

    return targetNotification;
}

AttackNotification UnitMaceI::Attack(DistrictBase * target)
{
    UseActionPoints(ACTION_POINTS);
    AttackNotification targetNotification = UnitBase::Attack(target);
    AttackNotification attackerNotification = ReceiveDamage(targetNotification.RiposteDamage);

    targetNotification.AttackerIsDead = attackerNotification.TargetIsDead;
    targetNotification.CanMove = true;

    return targetNotification;
}