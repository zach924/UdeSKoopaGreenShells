#include "ClientConnection.h"
#include <iostream>

void ClientConnection::ReadSocket()
{
	try
	{
		while (true)
		{
			RPCEvent newEvent{};
			m_tcpConnection.GetSocket().receive(boost::asio::buffer(reinterpret_cast<char*>(&newEvent.structType), sizeof(RPCStructType)));

			switch (newEvent.structType)
			{
				case RPCStructType::RPC_BASIC:
				{
					RPCBasicStruct* data = new RPCBasicStruct;
					m_tcpConnection.GetSocket().receive(boost::asio::buffer(reinterpret_cast<char*>(data), sizeof(RPCBasicStruct)));
					newEvent.data = data;
					break;
				}
				case RPCStructType::RPC_BASIC_TWO_POSITIONS:
				{
					RPCBasicTwoPositionsStruct* data = new RPCBasicTwoPositionsStruct;
					m_tcpConnection.GetSocket().receive(boost::asio::buffer(reinterpret_cast<char*>(data), sizeof(RPCBasicTwoPositionsStruct)));
					newEvent.data = data;
					break;
				}
				case RPCStructType::RPC_BASIC_CREATION:
				{
					RPCBasicCreationStruct* data = new RPCBasicCreationStruct;
					m_tcpConnection.GetSocket().receive(boost::asio::buffer(reinterpret_cast<char*>(data), sizeof(RPCBasicCreationStruct)));
					newEvent.data = data;
					break;
				}
			}

			m_queue->push(newEvent);
			std::cout << "Received an RPCEvent" << std::endl;
		}
	}
	catch (std::exception)
	{
		m_isSocketClosed = true;
	}
}

ClientConnection::ClientConnection()
{
}

void ClientConnection::StartThread()
{
	m_thread = new std::thread(&ClientConnection::ReadSocket, this);
}

void ClientConnection::SetPlayerID(int id)
{
	m_playerID = id;
}

int ClientConnection::GetPlayerID()
{
	return m_playerID;
}
void ClientConnection::SetIsSocketClosed(bool value)
{
	m_isSocketClosed = value;
}
bool ClientConnection::IsSocketClosed()
{
	return m_isSocketClosed;
}

void ClientConnection::SetQueuePointer(SynchronizedQueue<RPCEvent>* queue)
{
	m_queue = queue;
}

TCPConnection & ClientConnection::GetTCPConnection()
{
	return m_tcpConnection;
}
