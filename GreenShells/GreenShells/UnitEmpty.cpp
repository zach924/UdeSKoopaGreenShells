#include "UnitEmpty.h"
#include <algorithm>
#include <iostream>

UnitEmpty::UnitEmpty(int owner)
    : Unit<UnitEmpty>(owner, 0, 0, 0, 0, 0, UNIT_NAME, UNIT_TYPE)
{
}

UnitEmpty::~UnitEmpty()
{
}

std::shared_ptr<UnitBase> UnitEmpty::Clone()
{
    assert(false && "Why you trying to clone an empty unit >.>");
    return std::shared_ptr<UnitBase> { new UnitEmpty{ *this } };
}

void UnitEmpty::LoadTexture()
{
    try
    {
        m_unitTexture.LoadFromFile("Resources\\Sprite\\Units\\64x64\\emptyUnit.bmp");
    }
    catch (std::exception e)
    {
        std::string msg{ e.what() };
        std::cout << msg << std::endl;
    }
}

bool UnitEmpty::CanUpgrade()
{
    assert(false && "Should not use an Empty Unit. It cannot be placed on the map.");
    return false;
}

boost::property_tree::ptree UnitEmpty::Serialize()
{
    assert(false && "Should not try to serialize an empty unit. It cannot be placed on the map.");
    return boost::property_tree::ptree();
}

AttackNotification UnitEmpty::Attack(std::shared_ptr<UnitBase> target)
{
    assert(false && "Should not try to serialize an empty unit. It cannot be placed on the map.");
    return AttackNotification(0, false, false);
}

AttackNotification UnitEmpty::Attack(std::shared_ptr<DistrictBase> target)
{
    assert(false && "Should not try to serialize an empty unit. It cannot be placed on the map.");
    return AttackNotification(0, false, false);
}
