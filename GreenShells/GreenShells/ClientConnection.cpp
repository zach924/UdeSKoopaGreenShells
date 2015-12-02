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
                    int theoreticalSize = sizeof(RPCBasicStruct);
                    int actualSize = 0;
                    while (actualSize != theoreticalSize)
                    {
                        int receivedSize = static_cast<int>(m_tcpConnection.GetSocket().receive(boost::asio::buffer(data + actualSize, theoreticalSize - actualSize)));
                        actualSize += receivedSize;
                    }
                    newEvent.data = data;
                    break;
                }
                case RPCStructType::RPC_BASIC_ONE_POSITION:
                {
                    RPCBasicOnePositionStruct* data = new RPCBasicOnePositionStruct;
                    m_tcpConnection.GetSocket().receive(boost::asio::buffer(reinterpret_cast<char*>(data), sizeof(RPCBasicTwoPositionsStruct)));
                    newEvent.data = data;
                    break;
                }
                case RPCStructType::RPC_BASIC_TWO_POSITIONS:
                {
                    RPCBasicTwoPositionsStruct* data = new RPCBasicTwoPositionsStruct;
                    int theoreticalSize = sizeof(RPCBasicTwoPositionsStruct);
                    int actualSize = 0;
                    while (actualSize != theoreticalSize)
                    {
                        int receivedSize = static_cast<int>(m_tcpConnection.GetSocket().receive(boost::asio::buffer(data + actualSize, theoreticalSize - actualSize)));
                        actualSize += receivedSize;
                    }
                    newEvent.data = data;
                    break;
                }
                case RPCStructType::RPC_BASIC_TWO_POSITIONS_AND_COST:
                {
                    RPCBasicTwoPositionsAndCostStruct* data = new RPCBasicTwoPositionsAndCostStruct;
                    int theoreticalSize = sizeof(RPCBasicTwoPositionsAndCostStruct);
                    int actualSize = 0;
                    while (actualSize != theoreticalSize)
                    {
                        int receivedSize = static_cast<int>(m_tcpConnection.GetSocket().receive(boost::asio::buffer(data + actualSize, theoreticalSize - actualSize)));
                        actualSize += receivedSize;
                    }
                    newEvent.data = data;
                    break;
                }
                case RPCStructType::RPC_BASIC_CREATION:
                {
                    RPCBasicActorCreationStruct* data = new RPCBasicActorCreationStruct;
                    int theoreticalSize = sizeof(RPCBasicActorCreationStruct);
                    int actualSize = 0;
                    while (actualSize != theoreticalSize)
                    {
                        int receivedSize = static_cast<int>(m_tcpConnection.GetSocket().receive(boost::asio::buffer(data + actualSize, theoreticalSize - actualSize)));
                        actualSize += receivedSize;
                    }
                    newEvent.data = data;
                    break;
                }
                case RPCStructType::RPC_BASIC_DIPLOMACY_REQUEST:
                {
                    RPCBasicDiplomaticRequestStruct* data = new RPCBasicDiplomaticRequestStruct;
                    int theoreticalSize = sizeof(RPCBasicDiplomaticRequestStruct);
                    int actualSize = 0;
                    while (actualSize != theoreticalSize)
                    {
                        int receivedSize = static_cast<int>(m_tcpConnection.GetSocket().receive(boost::asio::buffer(data + actualSize, theoreticalSize - actualSize)));
                        actualSize += receivedSize;
                    }
                    newEvent.data = data;
                    break;
                }
                case RPCStructType::RPC_BASIC_UNLOCK_SKILL:
                {
                    RPCBasicUnlockSkill* data = new RPCBasicUnlockSkill;
                    int theoreticalSize = sizeof(RPCBasicUnlockSkill);
                    int actualSize = 0;
                    while (actualSize != theoreticalSize)
                    {
                        int receivedSize = static_cast<int>(m_tcpConnection.GetSocket().receive(boost::asio::buffer(data + actualSize, theoreticalSize - actualSize)));
                        actualSize += receivedSize;
                    }
                    newEvent.data = data;
                    break;
                }
                case RPCStructType::RPC_BASIC_DIPLOMACY_RESPONSE:
                {
                    RPCBasicDiplomaticResponseStruct* data = new RPCBasicDiplomaticResponseStruct;
                    int theoreticalSize = sizeof(RPCBasicDiplomaticResponseStruct);
                    int actualSize = 0;
                    while (actualSize != theoreticalSize)
                    {
                        int receivedSize = static_cast<int>(m_tcpConnection.GetSocket().receive(boost::asio::buffer(data + actualSize, theoreticalSize - actualSize)));
                        actualSize += receivedSize;
                    }
                    newEvent.data = data;
                    break;
                }
                default:
                    assert(false && "You must cast your new RPCStruct type here");
                    break;
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