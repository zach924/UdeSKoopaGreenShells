#include "UnitArcher.h"
#include <algorithm>
#include <iostream>

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
        m_Texture.LoadFromFile("..\\Sprite\\Units\\64x64\\Bow.bmp");
    }
    catch (std::exception e)
    {
        std::string msg{ e.what() };
        std::cout << msg << std::endl;
    }
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