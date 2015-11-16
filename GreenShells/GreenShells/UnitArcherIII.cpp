#include "UnitArcherIII.h"
#include <algorithm>
#include <iostream>
#include "GameSession.h"
#include "Player.h"

const char* UnitArcherIII::UNIT_NAME = "Archer MK3";

UnitArcherIII::UnitArcherIII(int owner)
    : Unit<UnitArcherIII>(owner, HEALTH, MOVE_RANGE, ATTACK_RANGE, ATTACK_DAMAGE)
{
}

UnitArcherIII::~UnitArcherIII()
{
}

UnitBase* UnitArcherIII::Clone()
{
    return new UnitArcherIII{ *this };
}

void UnitArcherIII::LoadTexture()
{
    try
    {
        m_Texture.LoadFromFile("..\\Sprite\\Units\\64x64\\bow3.bmp");
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

int UnitArcherIII::GetMaxHealth()
{
    return HEALTH;
}

const char * UnitArcherIII::GetName()
{
    return UNIT_NAME;
}

int UnitArcherIII::GetTypeAsInt()
{
    return UNIT_TYPE;
}

void UnitArcherIII::Heal(int health)
{
    m_health = std::min(m_health + health, HEALTH);
}

UnitArcherIII * UnitArcherIII::Deserialize(boost::property_tree::ptree node)
{
    UnitArcherIII* archer = new UnitArcherIII(node.get<int>("<xmlattr>.O"));
    archer->m_health = node.get<int>("<xmlattr>.H");

    return archer;
}