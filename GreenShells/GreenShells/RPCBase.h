#pragma once

#include <string>
#include "TCPConnection.h"

class RPCBase
{
public:
	static TCPConnection* s_connection;
	bool SendData(std::string data);
	bool SendData(char* data, int size);

public:
	static bool EstablishConnection(std::string ip, std::string port);
};