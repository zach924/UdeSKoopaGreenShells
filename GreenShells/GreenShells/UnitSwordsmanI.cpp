#include "UnitSwordsmanI.h"
#include <iostream>
#include "GameSession.h"
#include "Player.h"

const char* UnitSwordsmanI::UNIT_NAME = "Swordsman MK1";

UnitSwordsmanI::UnitSwordsmanI(int owner)
    : Unit<UnitSwordsmanI>(owner, HEALTH, ACTION_POINTS, MELEE_ATTACK_RANGE, ATTACK_DAMAGE)
{
}

UnitSwordsmanI::~UnitSwordsmanI()
{
}

UnitBase* UnitSwordsmanI::Clone()
{
    return new UnitSwordsmanI{ *this };
}

void UnitSwordsmanI::LoadTexture()
{
    try
    {
        m_Texture.LoadFromFile("..\\Sprite\\Units\\64x64\\sword.bmp");
    }
    catch (std::exception e)
    {
        std::string msg{ e.what() };
        std::cout << msg << std::endl;
    }
}

bool UnitSwordsmanI::CanUpgrade()
{
    Player* player = GameSession::GetInstance().GetWorldState()->GetPlayerCopy(GameSession::GetInstance().GetCurrentPlayerID());
    return player->GetArmySkillTree().SwordT2;
}

int UnitSwordsmanI::GetMaxHealth()
{
    return HEALTH;
}

const char * UnitSwordsmanI::GetName()
{
    return UNIT_NAME;
}

int UnitSwordsmanI::GetTypeAsInt()
{
    return UNIT_TYPE;
}

void UnitSwordsmanI::Heal(int health)
{
    m_health = std::min(m_health + health, HEALTH);
}

void UnitSwordsmanI::NotifyNewTurn(int turn)
{
    m_actionPointsLeft = ACTION_POINTS;
    std::shared_ptr<Player> currentPlayer{ GameSession::GetInstance().GetWorldState()->GetPlayerCopy(m_ownerID) };
    if (currentPlayer->GetUtilitySkillTree().MovementUpgrade)
    {
        m_actionPointsLeft += 1;
    }
}


// NEED TO PUT THIS IN EVERY MELEE UNIT, SO THEY CAN REECEIVE DAMAGE WHEN ATTACKING
AttackNotification UnitSwordsmanI::Attack(UnitBase * target)
{
    UseActionPoints(ACTION_POINTS);
    AttackNotification targetNotification = UnitBase::Attack(target);
    AttackNotification attackerNotification = ReceiveDamage(targetNotification.RiposteDamage);

    targetNotification.AttackerIsDead = attackerNotification.TargetIsDead;
    targetNotification.CanMove = true;

    return targetNotification;
}

AttackNotification UnitSwordsmanI::Attack(DistrictBase * target)
{
    UseActionPoints(ACTION_POINTS);
    AttackNotification targetNotification = UnitBase::Attack(target);
    AttackNotification attackerNotification = ReceiveDamage(targetNotification.RiposteDamage);

    targetNotification.AttackerIsDead = attackerNotification.TargetIsDead;
    targetNotification.CanMove = true;

    return targetNotification;
}

UnitSwordsmanI * UnitSwordsmanI::Deserialize(boost::property_tree::ptree node)
{
    UnitSwordsmanI* swordsman = new UnitSwordsmanI(node.get<int>("<xmlattr>.O"));
    swordsman->m_health = node.get<int>("<xmlattr>.H");
    swordsman->m_actionPointsLeft = node.get<int>("<xmlattr>.APL");

    return swordsman;
}