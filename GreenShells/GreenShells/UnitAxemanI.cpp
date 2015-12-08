#include "UnitAxemanI.h"
#include <algorithm>
#include <iostream>
#include "GameSession.h"
#include "Player.h"

UnitAxemanI::UnitAxemanI(int owner, bool hasBonusActionPoint)
    : Unit<UnitAxemanI>(owner, HEALTH, ACTION_POINTS, ATTACK_RANGE, ATTACK_DAMAGE, VIEW_RANGE, UNIT_NAME, UNIT_TYPE, WEAPON_COST, UPGRADE_TYPE)
{
    if (hasBonusActionPoint)
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
        m_unitTexture.LoadFromFile("Resources\\Sprite\\Units\\64x64\\axe.bmp");
    }
    catch (std::exception e)
    {
        std::string msg{ e.what() };
        std::cout << msg << std::endl;
    }
}

bool UnitAxemanI::CanUpgrade()
{
    auto player = GameSession::GetInstance().GetWorldState()->GetPlayerCopy(GetOwnerID());
    return player->GetArmySkillTree().AxeT2 && player->HasEnoughWeapons(GetWeaponCost());
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
    UseActionPoints(m_actionPointsLeft);
    AttackNotification targetNotification = UnitBase::Attack(target);
    AttackNotification attackerNotification = ReceiveDamage(targetNotification.RiposteDamage);

    targetNotification.AttackerIsDead = attackerNotification.TargetIsDead;
    targetNotification.CanMove = true;

    return targetNotification;
}

AttackNotification UnitAxemanI::Attack(std::shared_ptr<DistrictBase> target)
{
    UseActionPoints(m_actionPointsLeft);
    AttackNotification targetNotification = UnitBase::Attack(target);
    AttackNotification attackerNotification = ReceiveDamage(targetNotification.RiposteDamage);

    targetNotification.AttackerIsDead = attackerNotification.TargetIsDead;
    targetNotification.CanMove = true;

    return targetNotification;
}