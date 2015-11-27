#include "UnitAxemanI.h"
#include <algorithm>
#include <iostream>
#include "GameSession.h"
#include "ServerSession.h"
#include "Player.h"
#include "UnitAxemanII.h"
#include "Map.h"

const char* UnitAxemanI::UNIT_NAME = "Axeman MK1";

UnitAxemanI::UnitAxemanI(int owner)
    : Unit<UnitAxemanI>(owner, HEALTH, ACTION_POINTS, ATTACK_RANGE, ATTACK_DAMAGE, VIEW_RANGE)
{
    auto player = ServerSession::GetInstance().GetWorldState()->GetPlayerCopy(m_ownerID);
    if (player->GetUtilitySkillTree().MovementUpgrade)
    {
        m_actionPointsLeft += 1;
    }
}

UnitAxemanI::~UnitAxemanI()
{
}

std::shared_ptr<UnitBase> UnitAxemanI::Clone()
{
    return std::shared_ptr<UnitBase> { new UnitAxemanI{ *this } };
}

void UnitAxemanI::LoadTexture()
{
    try
    {
        m_Texture.LoadFromFile("..\\Sprite\\Units\\64x64\\axe.bmp");
    }
    catch (std::exception e)
    {
        std::string msg{ e.what() };
        std::cout << msg << std::endl;
    }
}

bool UnitAxemanI::CanUpgrade()
{
    auto player = GameSession::GetInstance().GetWorldState()->GetPlayerCopy(m_ownerID);
    return player->GetArmySkillTree().AxeT2 && player->HasRessourcesForUnit(GetUnitTier());
}

int UnitAxemanI::GetMaxHealth()
{
    return HEALTH;
}

const char * UnitAxemanI::GetName()
{
    return UNIT_NAME;
}

int UnitAxemanI::GetTypeAsInt()
{
    return UNIT_TYPE;
}

int UnitAxemanI::GetViewRange()
{
    return VIEW_RANGE;
}

int UnitAxemanI::GetUnitTier()
{
    return UNIT_TIER;
}

void UnitAxemanI::Heal(int health)
{
    m_health = std::min(m_health + health, HEALTH);
}

void UnitAxemanI::NotifyNewTurn(int turn)
{
    m_actionPointsLeft = ACTION_POINTS;
    auto player = ServerSession::GetInstance().GetWorldState()->GetPlayerCopy(m_ownerID);
    if (player->GetUtilitySkillTree().MovementUpgrade)
    {
        m_actionPointsLeft += 1;
    }
}

void UnitAxemanI::Upgrade(Map* map)
{
    map->GetTile(GetPosition())->SetUnit(std::shared_ptr<UnitBase>{new UnitAxemanII(GetOwnerID())});
}


std::shared_ptr<UnitAxemanI> UnitAxemanI::Deserialize(boost::property_tree::ptree node)
{
    std::shared_ptr<UnitAxemanI> axeman = std::shared_ptr<UnitAxemanI>{ new UnitAxemanI(node.get<int>("<xmlattr>.O")) };
    axeman->m_health = node.get<int>("<xmlattr>.H");
    axeman->m_actionPointsLeft = node.get<int>("<xmlattr>.APL");

    return axeman;
}

AttackNotification UnitAxemanI::Attack(std::shared_ptr<UnitBase> target)
{
    UseActionPoints(ACTION_POINTS);
    AttackNotification targetNotification = UnitBase::Attack(target);
    AttackNotification attackerNotification = ReceiveDamage(targetNotification.RiposteDamage);

    targetNotification.AttackerIsDead = attackerNotification.TargetIsDead;
    targetNotification.CanMove = true;

    return targetNotification;
}

AttackNotification UnitAxemanI::Attack(std::shared_ptr<DistrictBase> target)
{
    UseActionPoints(ACTION_POINTS);
    AttackNotification targetNotification = UnitBase::Attack(target);
    AttackNotification attackerNotification = ReceiveDamage(targetNotification.RiposteDamage);

    targetNotification.AttackerIsDead = attackerNotification.TargetIsDead;
    targetNotification.CanMove = true;

    return targetNotification;
}