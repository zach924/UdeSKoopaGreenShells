#pragma once

#include <string>
#include "TCPConnection.h"

class RPCBase
{
private:
	static TCPConnection* s_connection;

protected:
public:
	bool sendData(std::string data);
	bool sendData(char* data, int size);

public:
	static bool EstablishConnection(std::string ip, std::string port);
};