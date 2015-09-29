#include "MapLocal.h"
#include "Tile.h"
#include "Unit.h"
#include "District.h"
#include <iostream>

MapLocal::MapLocal()
	:Map()
{

}

MapLocal::~MapLocal()
{

}

bool MapLocal::MoveUnit(int id, Position unitLocation, Position newLocation)
{
	std::cout << "Received a move request by " << id << " from " << unitLocation << " to " << newLocation << std::endl;
	auto firstTile = GetTile(unitLocation);
	
	//No unit to select
	if (!firstTile->GetUnit())
	{
		return false;
	}

	//There is a unit be he does not belong to the requester
	if (firstTile->GetUnit()->GetPlayerOwnerID() != id)
	{
		return false;
	}
	
	auto secondTile = GetTile(newLocation);
	
	//Is second tile some place safe?
	if (!secondTile->CanTraverse())
	{
		return false;
	}

	//New Location is emtpy or there is a district and it's allied. Move him
	if ((!secondTile->GetUnit() && !secondTile->GetDistrict()) || (secondTile->GetDistrict() && secondTile->GetDistrict()->GetPlayerOwnerID() == id))
	{
		secondTile->SetUnit(firstTile->GetUnit());
		firstTile->SetUnit(nullptr);
		return true;
	}
	
	//Other cases are all refused
	return false;
}
