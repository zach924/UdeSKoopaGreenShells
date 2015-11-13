#include "UnitAxemanI.h"
#include <algorithm>
#include <iostream>
#include "GameSession.h"
#include "Player.h"

const char* UnitAxemanI::UNIT_NAME = "Axeman MK1";

UnitAxemanI::UnitAxemanI(int owner)
    : Unit<UnitAxemanI>(owner, HEALTH, MOVE_RANGE, ATTACK_RANGE, ATTACK_DAMAGE)
{
}

UnitAxemanI::~UnitAxemanI()
{
}

UnitBase* UnitAxemanI::Clone()
{
    return new UnitAxemanI{ *this };
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
    Player* player = GameSession::GetInstance().GetWorldState()->GetPlayerCopy(GameSession::GetInstance().GetCurrentPlayerID());
    return player->GetArmySkillTree().AxeT2;
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

void UnitAxemanI::Heal(int health)
{
    m_health = std::min(m_health + health, HEALTH);
}

UnitAxemanI * UnitAxemanI::Deserialize(boost::property_tree::ptree node)
{
    UnitAxemanI* axeman = new UnitAxemanI(node.get<int>("<xmlattr>.O"));
    axeman->m_health = node.get<int>("<xmlattr>.H");

    return axeman;
}

AttackNotification UnitAxemanI::Attack(UnitBase * target)
{
    AttackNotification targetNotification = UnitBase::Attack(target);
    AttackNotification attackerNotification = ReceiveDamage(targetNotification.RiposteDamage);

    targetNotification.AttackerIsDead = attackerNotification.TargetIsDead;
    targetNotification.CanMove = true;

    return targetNotification;
}

AttackNotification UnitAxemanI::Attack(DistrictBase * target)
{
    AttackNotification targetNotification = UnitBase::Attack(target);
    AttackNotification attackerNotification = ReceiveDamage(targetNotification.RiposteDamage);

    targetNotification.AttackerIsDead = attackerNotification.TargetIsDead;
    targetNotification.CanMove = true;

    return targetNotification;
}