#include "UnitEmpty.h"
#include <algorithm>
#include <iostream>

UnitEmpty::UnitEmpty(int owner)
    : Unit<UnitEmpty>(owner, 0, 0, 0, 0)
{
}

UnitEmpty::~UnitEmpty()
{
}

int UnitEmpty::GetTypeAsInt()
{
    assert(false && "Should no try to serialize an empty unit. It cannot be placed on the map");
    return -1;
}

void UnitEmpty::LoadTexture()
{
    try
    {
        m_Texture.LoadFromFile("..\\Sprite\\Units\\64x64\\emptyUnit.bmp");
    }
    catch (std::exception e)
    {
        std::string msg{ e.what() };
        std::cout << msg << std::endl;
    }
}

bool UnitEmpty::CanUpgrade()
{
	return false;
}

void UnitEmpty::Heal(int health)
{
    assert(false && "Should not try to heal an empty unit. It cannot be placed on the map.");
}

boost::property_tree::ptree UnitEmpty::Serialize()
{
    assert(false && "Should not try to serialize an empty unit. It cannot be placed on the map.");
    return boost::property_tree::ptree();
}

