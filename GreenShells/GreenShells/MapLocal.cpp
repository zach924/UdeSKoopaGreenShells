#include "MapLocal.h"

#include "TileGround.h"
#include "TileMountain.h"
#include "TileWater.h"

#include "Unit.h"
#include "District.h"
#include "DistrictCityCenter.h"
#include <boost\property_tree\ptree.hpp>
#include <iostream>
#include <exception>

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
		firstTile->GetUnit()->SetPosition(newLocation);
		firstTile->SetUnit(nullptr);
		return true;
	}

	//Other cases are all refused
	return false;
}

bool MapLocal::Attack(int ownerID, Position attackerPosition, Position targetPosition)
{
	std::cout << "Received an attack request by " << ownerID << " from " << attackerPosition << " to " << targetPosition << std::endl;

	auto targetTile = GetTile(targetPosition);
	auto attackerTile = GetTile(attackerPosition);
	auto attacker = attackerTile->GetUnit();

	// No unit on the Attacker tile
	if (!attacker) // TODO : might be useless, probably the selection manager that validate that
	{
		return false;
	}

	// Unit doesn't belong to the requester
	if (attacker->GetOwnerID() != ownerID) // TODO : might be useless, probably the selection manager that validate that
	{
		return false;
	}

	// Nothing to attack on target Tile
	if (targetTile->IsFree())
	{
		return false;
	}

	UnitBase* unitTargeted = targetTile->GetUnit();
	DistrictBase* districtTargeted = targetTile->GetDistrict();

	AttackNotification notification = unitTargeted ? attacker->Attack(unitTargeted) : attacker->Attack(districtTargeted);

	// Attacker is dead?
	if (notification.AttackerIsDead)
	{
		attackerTile->SetUnit(nullptr);
		delete attacker;
	}

	// Target is dead?
	if (notification.TargetIsDead)
	{
		if (unitTargeted)
		{
			targetTile->SetUnit(nullptr);
			delete unitTargeted;
		}
		else
		{
			if (typeid(districtTargeted) == typeid(DistrictCityCenter::tBase))
			{
				static_cast<DistrictCityCenter*>(districtTargeted)->ChangeOwner(ownerID);
				// for now player wont move on the citycenter if they take control of it
			}
			else
			{
				targetTile->SetDistrict(nullptr);
				delete districtTargeted;
			}
		}

		// Attacker is not dead, the tile is empty and attacker can move after combat (is melee?)
		if (!notification.AttackerIsDead && notification.CanMove && targetTile->IsFree())
		{
			MoveUnit(ownerID, attackerPosition, targetPosition);
		}
	}

	return true;
}

MapLocal* MapLocal::Deserialize(boost::property_tree::ptree mapNode)
{
	MapLocal* map = new MapLocal();
	int row = 0;
	for each (auto rowNode in mapNode)
	{
		if (rowNode.first == "SPS")
		{
			for each(auto spawnNode in rowNode.second)
			{
				if (spawnNode.first == "SP")
				{
					map->m_spawnPositions.emplace_back(spawnNode.second.get<int>("<xmlattr>.X"), spawnNode.second.get<int>("<xmlattr>.Y"));
				}
			}
		}
		else
		{
			int column = 0;
			for each(auto tileNode in rowNode.second)
			{
				if (tileNode.first == "T")
				{
				Position pos{ row, column };

					switch (tileNode.second.get<int>("<xmlattr>.TT"))
					{
					case 0:
						map->m_tiles[pos.X][pos.Y] = TileGround::Deserialize(tileNode.second, pos);
						break;
					case 1:
						map->m_tiles[pos.X][pos.Y] = TileMountain::Deserialize(tileNode.second, pos);
						break;
					case 2:
						map->m_tiles[pos.X][pos.Y] = TileWater::Deserialize(tileNode.second, pos);
						break;

					case -1:
					default:
						std::string msg = ("Error while loading the map, a tile is of type unknown.");
						throw new std::exception(msg.c_str());
						break;
					}
				}
				column++;
			}
			row++;
		}
	}

	return map;
}

