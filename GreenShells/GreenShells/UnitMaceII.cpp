#include "UnitMaceII.h"
#include <algorithm>
#include <iostream>
#include "GameSession.h"
#include "ServerSession.h"
#include "Player.h"

const char* UnitMaceII::UNIT_NAME = "Mace MK2";

UnitMaceII::UnitMaceII(int owner)
    : Unit<UnitMaceII>(owner, HEALTH, ACTION_POINTS, ATTACK_RANGE, ATTACK_DAMAGE, VIEW_RANGE)
{
    auto player = ServerSession::GetInstance().GetWorldState()->GetPlayerCopy(m_ownerID);
    if (player->GetUtilitySkillTree().MovementUpgrade)
    {
        m_actionPointsLeft += 1;
    }
}

UnitMaceII::~UnitMaceII()
{
}

std::shared_ptr<UnitBase> UnitMaceII::Clone()
{
    return std::shared_ptr<UnitBase> { new UnitMaceII{ *this } };
}

void UnitMaceII::LoadTexture()
{
    try
    {
        m_Texture.LoadFromFile("..\\Sprite\\Units\\64x64\\mace2.bmp");
    }
    catch (std::exception e)
    {
        std::string msg{ e.what() };
        std::cout << msg << std::endl;
    }
}

bool UnitMaceII::CanUpgrade()
{
    return false;
}

int UnitMaceII::GetMaxHealth()
{
    return HEALTH;
}

const char * UnitMaceII::GetName()
{
    return UNIT_NAME;
}

int UnitMaceII::GetTypeAsInt()
{
    return UNIT_TYPE;
}

int UnitMaceII::GetViewRange()
{
    return VIEW_RANGE;
}

void UnitMaceII::Heal(int health)
{
    m_health = std::min(m_health + health, HEALTH);
}

void UnitMaceII::NotifyNewTurn(int turn)
{
    m_actionPointsLeft = ACTION_POINTS;
    auto player = ServerSession::GetInstance().GetWorldState()->GetPlayerCopy(m_ownerID);
    if (player->GetUtilitySkillTree().MovementUpgrade)
    {
        m_actionPointsLeft += 1;
    }
}


std::shared_ptr<UnitMaceII> UnitMaceII::Deserialize(boost::property_tree::ptree node)
{
    std::shared_ptr<UnitMaceII> mace = std::shared_ptr<UnitMaceII>{ new UnitMaceII(node.get<int>("<xmlattr>.O")) };
    mace->m_health = node.get<int>("<xmlattr>.H");
    mace->m_actionPointsLeft = node.get<int>("<xmlattr>.APL");

    return mace;
}

AttackNotification UnitMaceII::Attack(std::shared_ptr<UnitBase> target)
{
    UseActionPoints(ACTION_POINTS);
    AttackNotification targetNotification = UnitBase::Attack(target);
    AttackNotification attackerNotification = ReceiveDamage(targetNotification.RiposteDamage);

    targetNotification.AttackerIsDead = attackerNotification.TargetIsDead;
    targetNotification.CanMove = true;

    return targetNotification;
}

AttackNotification UnitMaceII::Attack(std::shared_ptr<DistrictBase> target)
{
    UseActionPoints(ACTION_POINTS);
    AttackNotification targetNotification = UnitBase::Attack(target);
    AttackNotification attackerNotification = ReceiveDamage(targetNotification.RiposteDamage);

    targetNotification.AttackerIsDead = attackerNotification.TargetIsDead;
    targetNotification.CanMove = true;

    return targetNotification;
}
