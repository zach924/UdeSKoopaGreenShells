#include <sstream>
#include "MapRemote.h"
#include "RPCStructs.h"
#include "GameSession.h"

#include "TileGround.h"
#include "TileMountain.h"
#include "TileWater.h"
#include <boost\property_tree\ptree.hpp>

MapRemote::MapRemote()
	:Map()
{
}

MapRemote::~MapRemote()
{
}

bool MapRemote::MoveUnit(int ownerID, Position unitLocation, Position newLocation)
{
	//TODO Add checks on client to make sure that you can move this unit.
	std::stringstream ss;

	RPCStructType dataType{};
	dataType = RPCStructType::RPC_BASIC_TWO_POSITIONS;
	ss.write(reinterpret_cast<char*>(&dataType), sizeof(dataType));

	RPCBasicTwoPositionsStruct data;
	data.m_RPCClassMethod = RPCClassMethodType::Map_Move;
	data.m_turn = GameSession::GetInstance().GetWorldState()->GetCurrentTurn();
	data.m_requestingPlayerID = ownerID;
	data.m_firstPosition = unitLocation;
	data.m_secondPosition = newLocation;

	ss.write(reinterpret_cast<char*>(&data), sizeof(data));

	return SendData(ss.str());
}

MapRemote* MapRemote::Deserialize(boost::property_tree::ptree mapNode)
{
	MapRemote* map = new MapRemote();
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
