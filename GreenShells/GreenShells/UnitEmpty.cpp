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

UnitBase* UnitEmpty::Clone()
{
    assert(false && "Why you trying to clone an empty unit >.>");
    return new UnitEmpty{ *this };
}

int UnitEmpty::GetTypeAsInt()
{
	assert(false && "Should not use an Empty Unit. It cannot be placed on the map.");
    return -1;
}

void UnitEmpty::LoadTexture()
{
    try
    {
        m_Texture.LoadFromFile("..\\Sprite\\Units\\64x64\\emptyUnit.bmp");
		std::cout << "Loading UNIT_EMPTY" << std::endl;
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

void UnitEmpty::Heal(int health)
{
	assert(false && "Should not use an Empty Unit. It cannot be placed on the map.");
}

int UnitEmpty::GetMaxHealth()
{
	assert(false && "Should not use an Empty Unit. It cannot be placed on the map.");
	return 0;
}

const char * UnitEmpty::GetName()
{
	assert(false && "Should not use an Empty Unit. It cannot be placed on the map.");
	return nullptr;
}

boost::property_tree::ptree UnitEmpty::Serialize()
{
    assert(false && "Should not try to serialize an empty unit. It cannot be placed on the map.");
    return boost::property_tree::ptree();
}