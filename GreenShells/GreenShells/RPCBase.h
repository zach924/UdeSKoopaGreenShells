#pragma once

#include <string>
#include <boost/asio.hpp>


class RPCBase
{
	static boost::asio::ip::tcp::socket s_socket;
	static void CreateSocket(std::string ip, std::string port);


	void sendData();
};