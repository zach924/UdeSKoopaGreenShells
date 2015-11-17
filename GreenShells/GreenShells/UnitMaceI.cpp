#include "UnitMaceI.h"
#include <algorithm>
#include <iostream>
#include "GameSession.h"
#include "Player.h"

const char* UnitMaceI::UNIT_NAME = "Mace MK1";

UnitMaceI::UnitMaceI(int owner)
    : Unit<UnitMaceI>(owner, HEALTH, MOVE_RANGE, ATTACK_RANGE, ATTACK_DAMAGE)
{
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
    Player* player = GameSession::GetInstance().GetWorldState()->GetPlayerCopy(GameSession::GetInstance().GetCurrentPlayerID());
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

int UnitMaceI::GetUnitTier()
{
    return UNIT_TIER;
}

void UnitMaceI::Heal(int health)
{
    m_health = std::min(m_health + health, HEALTH);
}

UnitMaceI * UnitMaceI::Deserialize(boost::property_tree::ptree node)
{
    UnitMaceI* mace = new UnitMaceI(node.get<int>("<xmlattr>.O"));
    mace->m_health = node.get<int>("<xmlattr>.H");

    return mace;
}

AttackNotification UnitMaceI::Attack(UnitBase * target)
{
    AttackNotification targetNotification = UnitBase::Attack(target);
    AttackNotification attackerNotification = ReceiveDamage(targetNotification.RiposteDamage);

    targetNotification.AttackerIsDead = attackerNotification.TargetIsDead;
    targetNotification.CanMove = true;

    return targetNotification;
}

AttackNotification UnitMaceI::Attack(DistrictBase * target)
{
    AttackNotification targetNotification = UnitBase::Attack(target);
    AttackNotification attackerNotification = ReceiveDamage(targetNotification.RiposteDamage);

    targetNotification.AttackerIsDead = attackerNotification.TargetIsDead;
    targetNotification.CanMove = true;

    return targetNotification;
}