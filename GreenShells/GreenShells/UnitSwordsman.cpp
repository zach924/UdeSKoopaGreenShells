#include "UnitSwordsman.h"
#include <iostream>
#include "GameSession.h"
#include "Player.h"

const char* UnitSwordsman::UNIT_NAME = "Swordsman";

UnitSwordsman::UnitSwordsman(int owner)
    : Unit<UnitSwordsman>(owner, HEALTH, MOVE_RANGE, MELEE_ATTACK_RANGE, ATTACK_DAMAGE)
{
}

UnitSwordsman::~UnitSwordsman()
{
}

UnitBase* UnitSwordsman::Clone()
{
    return new UnitSwordsman{ *this };
}

void UnitSwordsman::LoadTexture()
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

bool UnitSwordsman::CanUpgrade()
{
    Player* player = GameSession::GetInstance().GetWorldState()->GetPlayerCopy(GameSession::GetInstance().GetCurrentPlayerID());
    return player->GetArmySkillTree().SwordT2;
}

int UnitSwordsman::GetMaxHealth()
{
    return HEALTH;
}

const char * UnitSwordsman::GetName()
{
    return UNIT_NAME;
}

int UnitSwordsman::GetTypeAsInt()
{
    return UNIT_TYPE;
}

void UnitSwordsman::Heal(int health)
{
    m_health = std::min(m_health + health, HEALTH);
}

// NEED TO PUT THIS IN EVERY MELEE UNIT, SO THEY CAN REECEIVE DAMAGE WHEN ATTACKING
AttackNotification UnitSwordsman::Attack(UnitBase * target)
{
    AttackNotification targetNotification = UnitBase::Attack(target);
    AttackNotification attackerNotification = ReceiveDamage(targetNotification.RiposteDamage);

    targetNotification.AttackerIsDead = attackerNotification.TargetIsDead;
    targetNotification.CanMove = true;

    return targetNotification;
}

AttackNotification UnitSwordsman::Attack(DistrictBase * target)
{
    AttackNotification targetNotification = UnitBase::Attack(target);
    AttackNotification attackerNotification = ReceiveDamage(targetNotification.RiposteDamage);

    targetNotification.AttackerIsDead = attackerNotification.TargetIsDead;
    targetNotification.CanMove = true;

    return targetNotification;
}

UnitSwordsman * UnitSwordsman::Deserialize(boost::property_tree::ptree node)
{
    UnitSwordsman* swordsman = new UnitSwordsman(node.get<int>("<xmlattr>.O"));
    swordsman->m_health = node.get<int>("<xmlattr>.H");

    return swordsman;
}