#include "UnitMaceI.h"
#include <algorithm>
#include <iostream>
#include "GameSession.h"
#include "Player.h"
#include "Map.h"
#include "UnitMaceII.h"

UnitMaceI::UnitMaceI(int owner, bool hasBonusActionPoint)
    : Unit<UnitMaceI>(owner, HEALTH, ACTION_POINTS, ATTACK_RANGE, ATTACK_DAMAGE, VIEW_RANGE, UNIT_NAME, UNIT_TYPE, WEAPON_COST)
{
    if (hasBonusActionPoint)
    {
        m_actionPointsLeft += 1;
    }
}

UnitMaceI::~UnitMaceI()
{
}

std::shared_ptr<UnitBase> UnitMaceI::Clone()
{
    return std::shared_ptr<UnitBase> { new UnitMaceI{ *this } };
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
    auto player = GameSession::GetInstance().GetWorldState()->GetPlayerCopy(GetOwnerID());
    return player->GetArmySkillTree().MaceT2 && player->HasEnoughWeapons(GetWeaponCost());
}

void UnitMaceI::Upgrade(Map* map)
{
    map->GetTile(GetPosition())->SetUnit(std::shared_ptr<UnitBase>{new UnitMaceII(GetOwnerID())});
}

std::shared_ptr<UnitMaceI> UnitMaceI::Deserialize(boost::property_tree::ptree node)
{
    std::shared_ptr<UnitMaceI> mace = std::shared_ptr<UnitMaceI>{ new UnitMaceI(node.get<int>("<xmlattr>.O")) };
    mace->m_health = node.get<int>("<xmlattr>.H");
    mace->m_actionPointsLeft = node.get<int>("<xmlattr>.APL");

    return mace;
}

AttackNotification UnitMaceI::Attack(std::shared_ptr<UnitBase> target)
{
    UseActionPoints(m_actionPointsLeft);
    AttackNotification targetNotification = UnitBase::Attack(target);
    AttackNotification attackerNotification = ReceiveDamage(targetNotification.RiposteDamage);

    targetNotification.AttackerIsDead = attackerNotification.TargetIsDead;
    targetNotification.CanMove = true;

    return targetNotification;
}

AttackNotification UnitMaceI::Attack(std::shared_ptr<DistrictBase> target)
{
    UseActionPoints(m_actionPointsLeft);
    AttackNotification targetNotification = UnitBase::Attack(target);
    AttackNotification attackerNotification = ReceiveDamage(targetNotification.RiposteDamage);

    targetNotification.AttackerIsDead = attackerNotification.TargetIsDead;
    targetNotification.CanMove = true;

    return targetNotification;
}