#include "UnitCannon.h"
#include <algorithm>
#include <iostream>
#include "GameSession.h"
#include "Player.h"

UnitCannon::UnitCannon(int owner, bool hasBonusActionPoint)
    : Unit<UnitCannon>(owner, HEALTH, ACTION_POINTS, ATTACK_RANGE, ATTACK_DAMAGE, VIEW_RANGE, UNIT_NAME, UNIT_TYPE, WEAPON_COST)
{
    if (hasBonusActionPoint)
    {
        m_actionPointsLeft += 1;
    }
}

UnitCannon::~UnitCannon()
{
}

std::shared_ptr<UnitBase> UnitCannon::Clone()
{
    return std::shared_ptr<UnitBase> { new UnitCannon{ *this } };
}

void UnitCannon::LoadTexture()
{
    try
    {
        m_unitTexture.LoadFromFile("Ressources\\Sprite\\Units\\64x64\\cannon.bmp");
    }
    catch (std::exception e)
    {
        std::string msg{ e.what() };
        std::cout << msg << std::endl;
    }
}

bool UnitCannon::CanUpgrade()
{
    return false;
}

std::shared_ptr<UnitCannon> UnitCannon::Deserialize(boost::property_tree::ptree node)
{
    std::shared_ptr<UnitCannon> cannon = std::shared_ptr<UnitCannon>{ new UnitCannon(node.get<int>("<xmlattr>.O")) };
    cannon->m_health = node.get<int>("<xmlattr>.H");
    cannon->m_actionPointsLeft = node.get<int>("<xmlattr>.APL");

    return cannon;
}
