#include "UnitArcherIII.h"
#include <algorithm>
#include <iostream>
#include "GameSession.h"
#include "Player.h"

UnitArcherIII::UnitArcherIII(int owner, bool hasBonusActionPoint)
    : Unit<UnitArcherIII>(owner, HEALTH, ACTION_POINTS, ATTACK_RANGE, ATTACK_DAMAGE, VIEW_RANGE, UNIT_NAME, UNIT_TYPE, WEAPON_COST)
{
    if (hasBonusActionPoint)
    {
        m_actionPointsLeft += 1;
    }
}

UnitArcherIII::~UnitArcherIII()
{
}

std::shared_ptr<UnitBase> UnitArcherIII::Clone()
{
    return std::shared_ptr<UnitBase> { new UnitArcherIII{ *this } };
}

void UnitArcherIII::LoadTexture()
{
    try
    {
        m_unitTexture.LoadFromFile("Ressources\\Sprite\\Units\\64x64\\bow3.bmp");
    }
    catch (std::exception e)
    {
        std::string msg{ e.what() };
        std::cout << msg << std::endl;
    }
}

bool UnitArcherIII::CanUpgrade()
{
    return false;
}

std::shared_ptr<UnitArcherIII> UnitArcherIII::Deserialize(boost::property_tree::ptree node)
{
    std::shared_ptr<UnitArcherIII> archer = std::shared_ptr<UnitArcherIII>{ new UnitArcherIII(node.get<int>("<xmlattr>.O")) };
    archer->m_health = node.get<int>("<xmlattr>.H");
    archer->m_actionPointsLeft = node.get<int>("<xmlattr>.APL");

    return archer;
}