#pragma once

#include <string>
#include "Position.h"

using namespace std;

/*
When creating a new struct to send over the network, don't forget to add the corresponding name in the enum 
*/
struct JoinGameStruct
{
	int playerID;
};

enum RPCStructType
{
	JOIN_GAME,
	RPC_BASIC,
	RPC_BASIC_TWO_POSITIONS,

};

enum RPCClassMethodType
{
	//Class_Method,
	Map_Move,
	Map_Attack

};

struct RPCBasicStruct
{
	int m_turn;
	int m_requestingPlayerID;
	RPCClassMethodType m_RPCClassMethod;

	virtual bool virtualMethodForCompile()
	{ return false;	}
};

struct RPCBasicTwoPositionsStruct : public RPCBasicStruct
{
	Position m_firstPosition;
	Position m_secondPosition;
};

struct RPCEvent
{
	RPCStructType structType;
	RPCBasicStruct* data;
};