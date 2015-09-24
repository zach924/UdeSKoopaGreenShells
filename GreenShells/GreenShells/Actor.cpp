#include "Actor.h"

Actor::Actor()
    :m_position(-1,-1),
    m_foodCost(0),
    m_scienceCost(0),
    m_weaponCost(0),
    m_foodRatioBonus(0.0),
    m_scienceRatioBonus(0.0),
    m_weaponRatioBonus(0.0)
{
}


Actor::~Actor()
{
}
