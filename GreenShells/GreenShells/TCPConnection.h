#pragma once
#include <string>
#include <boost/asio.hpp>

class TCPConnection
{
private:
	static boost::asio::io_service s_ioService;
	boost::asio::ip::tcp::socket m_socket;

public:
	TCPConnection(std::string ip, std::string port);
	boost::asio::ip::tcp::socket& getSocket();
};