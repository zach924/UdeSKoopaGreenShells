#include "RPCBase.h"
#include <iostream>
#include <boost/make_unique.hpp>

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#ifdef _DEBUG
#define DEBUG_CLIENTBLOCK   new( _CLIENT_BLOCK, __FILE__, __LINE__)
#else
#define DEBUG_CLIENTBLOCK
#endif // _DEBUG

#ifdef _DEBUG
#define new DEBUG_CLIENTBLOCK
#endif

TCPConnection* RPCBase::s_connection = nullptr;

bool RPCBase::SendData(std::string data)
{
	try
	{
		s_connection->GetSocket().send(boost::asio::buffer(data));
		return true;
	}
	catch (std::exception)
	{
		return false;
	}
}

bool RPCBase::SendData(char* data, int size)
{
	try
	{
		s_connection->GetSocket().send(boost::asio::buffer(data, size));
		return true;
	}
	catch (std::exception)
	{
		return false;
	}
}

bool RPCBase::EstablishConnection(std::string ip, std::string port)
{
	try
	{
		s_connection = new TCPConnection(ip, port);
		return true;
	}
	catch (boost::system::system_error)
	{
		return false;
	}
}

TCPConnection* RPCBase::GetConnection()
{
	return s_connection;
}