#include "TCPConnection.h"

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

using boost::asio::ip::tcp;

boost::asio::io_service TCPConnection::s_ioService{};

TCPConnection::TCPConnection()
	: m_socket{ s_ioService }
{

}

TCPConnection::TCPConnection(std::string ip, std::string port)
	: m_socket {	s_ioService }
{
	tcp::resolver resolver(s_ioService);
	tcp::resolver::query query(ip, port);
	tcp::resolver::iterator endpoint_iterator = resolver.resolve(query);
	tcp::resolver::iterator end;

	boost::system::error_code error = boost::asio::error::host_not_found;
	while (error && endpoint_iterator != end)
	{
		m_socket.close();
		m_socket.connect(*endpoint_iterator++, error);
	}
	if (error)
	{
		throw boost::system::system_error(error);
	}
}

boost::asio::ip::tcp::socket& TCPConnection::GetSocket()
{
	return m_socket;
}
