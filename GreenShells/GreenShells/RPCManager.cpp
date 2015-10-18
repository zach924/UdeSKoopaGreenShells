#include <iostream>
#include <thread>
#include <sstream>

#include "RPCManager.h"
#include "ClientConnection.h"
#include "RPCDispatcher.h"
#include "Player.h"
#include "ServerSession.h"

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
			try
			{
				ClientConnection* newClient = new ClientConnection{};
				acceptor.accept(newClient->GetTCPConnection().GetSocket());
				newClient->SetQueuePointer(m_events);
				newClient->SetPlayerID(ServerSession::GetInstance().AddPlayer());
				newClient->StartThread();
				m_clients.push_back(newClient);

				//inform client of his id
				std::stringstream ss;
				RPCStructType dataType{};
				dataType = RPCStructType::JOIN_GAME;
				ss.write(reinterpret_cast<char*>(&dataType), sizeof(dataType));
				JoinGameStruct data;
				data.playerID = newClient->GetPlayerID();
				ss.write(reinterpret_cast<char*>(&data), sizeof(data));
				newClient->GetTCPConnection().GetSocket().send(boost::asio::buffer(ss.str()));

				//replicate for new client
				ServerSession::GetInstance().Replicate();
			}
			catch (std::exception e)
			{
				cout << e.what() << endl;
			}
		}
	});
}

void RPCManager::SetEventQueue(SynchronizedQueue<RPCEvent>* queue)
{
	m_events = queue;
}

SynchronizedQueue<RPCEvent>* RPCManager::GetEventQueue()
{
	return m_events;
}

void RPCManager::SendToClients(std::string data)
{
	for (auto client : m_clients)
	{
		try
		{
			client->GetTCPConnection().GetSocket().send(boost::asio::buffer(data));
		}
		catch (std::exception)
		{
			//Client has diconnected, it should be cleaned up next tick
		}
	}
}

std::vector<int> RPCManager::GetDisconnectedPlayers()
{
	std::vector<int> playerIDDisconnected;
	for (auto client : m_clients)
	{
		if (!client->GetTCPConnection().GetSocket().is_open())
		{
			std::cout << "Player " << client->GetPlayerID() << " has disconnected." << std::endl;
			playerIDDisconnected.push_back(client->GetPlayerID());
		}
	}

	//Clean up disconnected players
	for (auto playerID : playerIDDisconnected)
	{
		for (auto it = m_clients.begin(); it != m_clients.end(); ++it)
		{
			if ((*it)->GetPlayerID() == playerID)
			{
				m_clients.erase(it);
				break;
			}
		}
	}
	return playerIDDisconnected;
}

