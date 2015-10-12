#include "CityCenter.h"
#include "GameSession.h"


CityCenter::CityCenter(int owner) 
	: DistrictDefensive(owner, 100)
{
	GameSession::GetInstance().GetWorldState()->GetPlayer(m_ownerID).AddCityCenter();
}

CityCenter::~CityCenter()
{
	GameSession::GetInstance().GetWorldState()->GetPlayer(m_ownerID).RemoveCityCenter();
}
