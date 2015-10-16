#include "RPCBase.h"
#include <iostream>
#include <boost/make_unique.hpp>

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