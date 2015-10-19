#include "District.h"
#include "Texture.h"


District::District(int& ownerID)
	:Actor(ownerID)
{
}

District::~District()
{
}


Texture CityCenter::tBase::m_Texture = {};
Texture Farm::tBase::m_Texture = {};
