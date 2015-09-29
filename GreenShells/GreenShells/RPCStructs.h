#pragma once

#include <string>
#include "Position.h"

using namespace std;

/*
When creating a new struct to send over the network, don't forget to add the corresponding name in the enum 
*/
enum RPCStructType
{
	RPC_BASIC,
	RPC_BASIC_TWO_POSITIONS,

};

enum RPCClassMethodType
{
	Map_Move,

};


struct RPCBasicStruct
{
	int m_requestingPlayerID;
	int m_RPCClassMethod;

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