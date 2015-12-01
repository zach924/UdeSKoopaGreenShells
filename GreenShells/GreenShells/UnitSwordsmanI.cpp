#include "UnitSwordsmanI.h"
#include <iostream>
#include "GameSession.h"
#include "Player.h"

UnitSwordsmanI::UnitSwordsmanI(int owner, bool hasBonusActionPoint)
    : Unit<UnitSwordsmanI>(owner, HEALTH, ACTION_POINTS, MELEE_ATTACK_RANGE, ATTACK_DAMAGE, VIEW_RANGE, UNIT_NAME, UNIT_TYPE, WEAPON_COST, NO_FOOD_COST, UPGRADE_TYPE)
{
    if (hasBonusActionPoint)
    {
        m_actionPointsLeft += 1;
    }
}

UnitSwordsmanI::~UnitSwordsmanI()
{
}

std::shared_ptr<UnitBase> UnitSwordsmanI::Clone()
{
    return std::shared_ptr<UnitBase> { new UnitSwordsmanI{ *this } };
}

void UnitSwordsmanI::LoadTexture()
{
    try
    {
        m_unitTexture.LoadFromFile("..\\Sprite\\Units\\64x64\\sword.bmp");
    }
    catch (std::exception e)
    {
        std::string msg{ e.what() };
        std::cout << msg << std::endl;
    }
}

bool UnitSwordsmanI::CanUpgrade()
{
    auto player = GameSession::GetInstance().GetWorldState()->GetPlayerCopy(GetOwnerID());
    return player->GetArmySkillTree().SwordT2 && player->HasEnoughWeapons(GetWeaponCost());
}

// NEED TO PUT THIS IN EVERY MELEE UNIT, SO THEY CAN REECEIVE DAMAGE WHEN ATTACKING
AttackNotification UnitSwordsmanI::Attack(std::shared_ptr<UnitBase> target)
{
    UseActionPoints(m_actionPointsLeft);
    AttackNotification targetNotification = UnitBase::Attack(target);
    AttackNotification attackerNotification = ReceiveDamage(targetNotification.RiposteDamage);

    targetNotification.AttackerIsDead = attackerNotification.TargetIsDead;
    targetNotification.CanMove = true;

    return targetNotification;
}

AttackNotification UnitSwordsmanI::Attack(std::shared_ptr<DistrictBase> target)
{
    UseActionPoints(m_actionPointsLeft);
    AttackNotification targetNotification = UnitBase::Attack(target);
    AttackNotification attackerNotification = ReceiveDamage(targetNotification.RiposteDamage);

    targetNotification.AttackerIsDead = attackerNotification.TargetIsDead;
    targetNotification.CanMove = true;

    return targetNotification;
}

std::shared_ptr<UnitSwordsmanI> UnitSwordsmanI::Deserialize(boost::property_tree::ptree node)
{
    std::shared_ptr<UnitSwordsmanI> swordsman = std::shared_ptr<UnitSwordsmanI>{ new UnitSwordsmanI(node.get<int>("<xmlattr>.O")) };
    swordsman->m_health = node.get<int>("<xmlattr>.H");
    swordsman->m_actionPointsLeft = node.get<int>("<xmlattr>.APL");

    return swordsman;
}