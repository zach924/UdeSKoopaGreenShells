#include "Archer.h"
#include <algorithm>
#include <iostream>

Archer::Archer(int owner)
	: Unit<Archer>(owner, HEALTH, ATTACK_RANGE, ATTACK_DAMAGE)
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

Archer * Archer::Deserialize(boost::property_tree::ptree node)
{
	Archer* archer = new Archer(node.get<int>("<xmlattr>.O"));
	archer->m_health = node.get<int>("<xmlattr>.H");

	return archer;
}

