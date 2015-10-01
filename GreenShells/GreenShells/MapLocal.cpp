#include "MapLocal.h"

#include "TileGround.h"
#include "TileMountain.h"
#include "TileWater.h"

#include "Unit.h"
#include "District.h"
#include <boost\property_tree\ptree.hpp>
#include <iostream>

MapLocal::MapLocal()
	:Map()
{

}

MapLocal::~MapLocal()
{

}

bool MapLocal::MoveUnit(int ownerID, Position unitLocation, Position newLocation)
{
	std::cout << "Received a move request by " << ownerID << " from " << unitLocation << " to " << newLocation << std::endl;
	auto firstTile = GetTile(unitLocation);
	
	//No unit to select
	if (!firstTile->GetUnit())
	{
		return false;
	}

	//There is a unit be he does not belong to the requester
	if (firstTile->GetUnit()->GetOwnerID() != ownerID)
	{
		return false;
	}
	
	auto secondTile = GetTile(newLocation);
	
	//Is second tile some place safe?
	//TODO : Add abilities that allows mountain & water passage.
	if (!secondTile->CanTraverse())
	{
		return false;
	}

	//New Location is emtpy or there is a district and it's allied. Move him
	if ((!secondTile->GetUnit() && !secondTile->GetDistrict()) || (secondTile->GetDistrict() && secondTile->GetDistrict()->GetOwnerID() == ownerID))
	{
		secondTile->SetUnit(firstTile->GetUnit());
		firstTile->SetUnit(nullptr);
		return true;
	}
	
	//Other cases are all refused
	return false;
}

MapLocal* MapLocal::Deserialize(boost::property_tree::ptree mapNode)
{
	MapLocal* map = new MapLocal();
	for each (auto rowNode in mapNode)
	{
		for each(auto tileNode in rowNode.second)
		{
			if (tileNode.first == "Tile")
			{
				Position pos{ tileNode.second.get<int>("<xmlattr>.X"), tileNode.second.get<int>("<xmlattr>.Y") };

				switch (tileNode.second.get<int>("<xmlattr>.Type"))
				{
				case 0:
					map->m_tiles[pos.X][pos.Y] = TileGround::Deserialize(tileNode.second, pos);
					break;
				case 1:
					map->m_tiles[pos.X][pos.Y] = TileMountain::Deserialize(tileNode.second);
					break;
				case 2:
					map->m_tiles[pos.X][pos.Y] = TileWater::Deserialize(tileNode.second);
					break;

				case -1:
				default:
					// Probably throw error for corrupt file
					break;
				}
			}
		}
	}

	return map;
}
