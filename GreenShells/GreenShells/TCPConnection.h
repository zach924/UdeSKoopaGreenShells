#pragma once
#include <string>
#include <boost/asio.hpp>

class TCPConnection
{
private:
    boost::asio::ip::tcp::socket m_socket;

public:
    static boost::asio::io_service s_ioService;

    TCPConnection();
    TCPConnection(std::string ip, std::string port);
    boost::asio::ip::tcp::socket& GetSocket();
};