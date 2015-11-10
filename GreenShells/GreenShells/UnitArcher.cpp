#include "UnitArcher.h"
#include <algorithm>
#include <iostream>

const char* UnitArcher::UNIT_NAME = "Archer";

UnitArcher::UnitArcher(int owner)
    : Unit<UnitArcher>(owner, HEALTH, MOVE_RANGE, ATTACK_RANGE, ATTACK_DAMAGE)
{
}

UnitArcher::~UnitArcher()
{
}

UnitBase* UnitArcher::Clone()
{
    return new UnitArcher{ *this };
}

void UnitArcher::LoadTexture()
{
    try
    {
        m_Texture.LoadFromFile("..\\Sprite\\Units\\64x64\\bow.bmp");
		std::cout << "Loading UNIT_ARCHER" << std::endl;
    }
    catch (std::exception e)
    {
        std::string msg{ e.what() };
        std::cout << msg << std::endl;
    }
}

bool UnitArcher::CanUpgrade()
{
    return false; // TODO :  Get bit field in player
}

int UnitArcher::GetMaxHealth()
{
	return HEALTH;
}

const char * UnitArcher::GetName()
{
	return UNIT_NAME;
}

int UnitArcher::GetTypeAsInt()
{
    return UNIT_TYPE;
}

void UnitArcher::Heal(int health)
{
    m_health = std::min(m_health + health, HEALTH);
}

UnitArcher * UnitArcher::Deserialize(boost::property_tree::ptree node)
{
    UnitArcher* archer = new UnitArcher(node.get<int>("<xmlattr>.O"));
    archer->m_health = node.get<int>("<xmlattr>.H");

    return archer;
}