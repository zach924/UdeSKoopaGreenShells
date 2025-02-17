#include "UnitBuilder.h"
#include <algorithm>
#include <iostream>
#include "GameSession.h"
#include "Player.h"

UnitBuilder::UnitBuilder(int owner, bool hasBonusActionPoint)
    : Unit<UnitBuilder>(owner, HEALTH, ACTION_POINTS, ATTACK_RANGE, ATTACK_DAMAGE, VIEW_RANGE, UNIT_NAME, UNIT_TYPE, WEAPON_COST, UPGRADE_TYPE)
{
    if (hasBonusActionPoint)
    {
        m_actionPointsLeft += 1;
    }
}

UnitBuilder::~UnitBuilder()
{
}

std::shared_ptr<UnitBase> UnitBuilder::Clone()
{
    return std::shared_ptr<UnitBase> { new UnitBuilder{ *this } };
}

void UnitBuilder::LoadTexture()
{
    try
    {
        m_unitTexture.LoadFromFile("Resources\\Sprite\\Units\\64x64\\builder.bmp");
    }
    catch (std::exception e)
    {
        std::string msg{ e.what() };
        std::cout << msg << std::endl;
    }
}

bool UnitBuilder::CanUpgrade()
{
    return true;
}

std::shared_ptr<UnitBuilder> UnitBuilder::Deserialize(boost::property_tree::ptree node)
{
    std::shared_ptr<UnitBuilder> builder = std::shared_ptr<UnitBuilder>{ new UnitBuilder(node.get<int>("<xmlattr>.O")) };
    builder->m_health = node.get<int>("<xmlattr>.H");
    builder->m_actionPointsLeft = node.get<int>("<xmlattr>.APL");

    return builder;
}

