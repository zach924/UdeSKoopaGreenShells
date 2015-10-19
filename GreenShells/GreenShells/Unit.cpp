#include "Unit.h"
#include "Texture.h"

Unit::Unit(int& ownerID)
	:Actor(ownerID)
{
}



Texture Swordsman::tBase::m_Texture = {};
Texture Archer::tBase::m_Texture = {};
