#include "Archer.h"
#include <algorithm>
#include <iostream>

Archer::Archer(int owner)
	: Unit<Archer>(owner, HEALTH, 3, ATTACK_DAMAGE)
{
}

Archer::~Archer()
{
}

void Archer::LoadTexture()
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

int Archer::GetTypeAsInt()
{
	return UNIT_TYPE;
}

void Archer::Heal(int health)
{
	m_health = std::min(m_health + health, HEALTH);
}

boost::property_tree::ptree Archer::Serialize()
{
	return boost::property_tree::ptree();
}

