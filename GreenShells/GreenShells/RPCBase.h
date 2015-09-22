#pragma once

#include <string>
#include "TCPConnection.h"

class RPCBase
{
private:
	static TCPConnection* s_connection;

protected:
	void sendData(std::string data);

public:
	static bool EstablishConnection(std::string ip, std::string port);
};