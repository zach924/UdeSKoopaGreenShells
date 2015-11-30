#include "UnitArcherI.h"
#include <algorithm>
#include <iostream>
#include "GameSession.h"
#include "Player.h"
#include "UnitArcherII.h"
#include "Map.h"

UnitArcherI::UnitArcherI(int owner, bool hasBonusActionPoint)
    : Unit<UnitArcherI>(owner, HEALTH, ACTION_POINTS, ATTACK_RANGE, ATTACK_DAMAGE, VIEW_RANGE, UNIT_NAME, UNIT_TYPE, WEAPON_COST)
{
    if (hasBonusActionPoint)
    {
        m_actionPointsLeft += 1;
    }
}

UnitArcherI::~UnitArcherI()
{
}

std::shared_ptr<UnitBase> UnitArcherI::Clone()
{
    return std::shared_ptr<UnitBase> { new UnitArcherI{ *this } };
}

void UnitArcherI::LoadTexture()
{
    try
    {
        m_Texture.LoadFromFile("..\\Sprite\\Units\\64x64\\bow.bmp");
    }
    catch (std::exception e)
    {
        std::string msg{ e.what() };
        std::cout << msg << std::endl;
    }
}

bool UnitArcherI::CanUpgrade()
{
    auto player = GameSession::GetInstance().GetWorldState()->GetPlayerCopy(GetOwnerID());
    return player->GetArmySkillTree().ArcherT2 && player->HasEnoughWeapons(GetWeaponCost());
}

void UnitArcherI::Upgrade(Map* map)
{
    map->GetTile(GetPosition())->SetUnit(std::shared_ptr<UnitBase>{new UnitArcherII(GetOwnerID())});
}

std::shared_ptr<UnitArcherI> UnitArcherI::Deserialize(boost::property_tree::ptree node)
{
    std::shared_ptr<UnitArcherI> archer = std::shared_ptr<UnitArcherI>{ new UnitArcherI(node.get<int>("<xmlattr>.O")) };
    archer->m_health = node.get<int>("<xmlattr>.H");
    archer->m_actionPointsLeft = node.get<int>("<xmlattr>.APL");

    return archer;
}