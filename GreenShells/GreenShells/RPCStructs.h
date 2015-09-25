#pragma once

#include <string>
#include "Position.h"

using namespace std;

/*
When creating a new struct to send over the network, don't forget to add the corresponding name in the enum 
*/
enum RPCStructType : uint8_t
{
	RPC_BASIC,
	RPC_BASIC_TWO_POSITIONS,

};

struct RPCBasicStruct
{
	char m_className[100];
	char m_methodName[100];

	string GetClassNameAsString()
	{ return m_className; }

	void SetClassName(string name)
	{ strcpy_s(m_className, name.c_str()); }

	string GetMethodNameAsString()
	{ return m_methodName; }

	void SetMethodName(string name)
	{ strcpy_s(m_methodName, name.c_str()); }
};

struct RPCBasicTwoPositionsStruct : RPCBasicStruct
{
	Position m_firstPosition;
	Position m_secondPosition;
};



struct RPCEvent
{
	RPCStructType structType;
	RPCBasicStruct* data;
};