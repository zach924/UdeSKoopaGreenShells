#include <iostream>
#include <thread>
#include "RPCManager.h"
#include "ClientConnection.h"

using boost::asio::ip::tcp;

RPCManager::RPCManager(int port)
	: m_port(port)
{

}

void RPCManager::StartListening()
{
	m_thread = new std::thread([&]() {
		tcp::acceptor acceptor(TCPConnection::s_ioService, tcp::endpoint(tcp::v4(), m_port));

		while (true)
		{
			ClientConnection* newClient = new ClientConnection{};
			acceptor.accept(newClient->GetTCPConnection().GetSocket());
			newClient->SetQueuePointer(&m_events);
			newClient->StartThread();
			m_clients.push_back(newClient);
		}
	});
}
