#pragma once

#include <string>

using namespace std;

/*
When creating a new struct to send over the network, don't forget to add the corresponding name in the enum 
*/
enum RPCStructType : uint8_t
{
	RPC_BASIC,
	RPC_BASIC_TWO_POSITIONS,

};


struct RPCBasic
{
	string m_className;
	string m_methodName;
};

struct RPCBasicTwoPositions : RPCBasic
{
//position 1
//position 2
};