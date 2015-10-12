#include "Swordsman.h"
#include <iostream>

Swordsman::Swordsman(int owner)
	: UnitMelee(owner, ATTACK_DAMAGE)
{
}

Swordsman::~Swordsman()
{
}

void Swordsman::LoadTexture()
{
	try
	{
		m_Texture.LoadFromFile("..\\Sprite\\Units\\64x64\\Sword.bmp");
	}
	catch (std::exception e)
	{
		std::string msg{ e.what() };
		std::cout << msg << std::endl;
	}
}
