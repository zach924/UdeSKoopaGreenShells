#include <sstream>
#include "MapRemote.h"
#include "RPCStructs.h"
#include "GameSession.h"

MapRemote::MapRemote()
	:Map()
{
}

MapRemote::~MapRemote()
{
}

bool MapRemote::MoveUnit(int id, Position unitLocation, Position newLocation)
{
	//TODO Add checks on client to make sure that you can move this unit.
	std::stringstream ss;

	RPCStructType dataType{};
	dataType = RPCStructType::RPC_BASIC_TWO_POSITIONS;
	ss.write(reinterpret_cast<char*>(&dataType), sizeof(dataType));

	RPCBasicTwoPositionsStruct data;
	data.m_RPCClassMethod = RPCClassMethodType::Map_Move;
	data.m_requestingPlayerID = id;
	data.m_firstPosition = unitLocation;
	data.m_secondPosition = newLocation;

	ss.write(reinterpret_cast<char*>(&data), sizeof(data));

	return SendData(ss.str());
}
