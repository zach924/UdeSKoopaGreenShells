#include "RPCBase.h"
#include <boost/make_unique.hpp>

TCPConnection* RPCBase::s_connection = nullptr;

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

void RPCBase::sendData(std::string data)
{
	s_connection->getSocket().send(boost::asio::buffer(data));
}