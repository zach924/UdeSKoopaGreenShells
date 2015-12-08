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
                    int theoreticalSize = sizeof(RPCBasicOnePositionStruct);
                    int actualSize = 0;
                    while (actualSize != theoreticalSize)
                    {
                        int receivedSize = static_cast<int>(m_tcpConnection.GetSocket().receive(boost::asio::buffer(data + actualSize, theoreticalSize - actualSize)));
                        actualSize += receivedSize;
                    }
                    //Temp hack
                    RPCBasicOnePositionStruct* secondData = new RPCBasicOnePositionStruct;
                    secondData->m_RPCClassMethod = data->m_RPCClassMethod;
                    secondData->m_turn = data->m_turn;
                    secondData->m_requestingPlayerID = data->m_requestingPlayerID;
                    secondData->m_position = data->m_position;
                    newEvent.data = secondData;
                    delete data;
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
                    //Temp hack
                    RPCBasicTwoPositionsStruct* secondData = new RPCBasicTwoPositionsStruct;
                    secondData->m_RPCClassMethod = data->m_RPCClassMethod;
                    secondData->m_turn = data->m_turn;
                    secondData->m_requestingPlayerID = data->m_requestingPlayerID;
                    secondData->m_firstPosition = data->m_firstPosition;
                    secondData->m_secondPosition = data->m_secondPosition;
                    newEvent.data = secondData;
                    delete data;
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
                    //Temp hack
                    RPCBasicTwoPositionsAndCostStruct* secondData = new RPCBasicTwoPositionsAndCostStruct;
                    secondData->m_RPCClassMethod = data->m_RPCClassMethod;
                    secondData->m_turn = data->m_turn;
                    secondData->m_requestingPlayerID = data->m_requestingPlayerID;
                    secondData->m_firstPosition = data->m_firstPosition;
                    secondData->m_secondPosition = data->m_secondPosition;
                    secondData->m_actionCost = data->m_actionCost;
                    newEvent.data = secondData;
                    delete data;
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
                    //Temp hack
                    RPCBasicActorCreationStruct* secondData = new RPCBasicActorCreationStruct;
                    secondData->m_RPCClassMethod = data->m_RPCClassMethod;
                    secondData->m_turn = data->m_turn;
                    secondData->m_requestingPlayerID = data->m_requestingPlayerID;
                    secondData->m_actorType = data->m_actorType;
                    secondData->m_positionToCreate = data->m_positionToCreate;
                    newEvent.data = secondData;
                    delete data;
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
                    //Temp hack
                    RPCBasicDiplomaticRequestStruct* secondData = new RPCBasicDiplomaticRequestStruct;
                    secondData->m_RPCClassMethod = data->m_RPCClassMethod;
                    secondData->m_turn = data->m_turn;
                    secondData->m_requestingPlayerID = data->m_requestingPlayerID;
                    secondData->m_otherPlayerId = data->m_otherPlayerId;
                    newEvent.data = secondData;
                    delete data;
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
                    //Temp hack
                    RPCBasicUnlockSkill* secondData = new RPCBasicUnlockSkill;
                    secondData->m_RPCClassMethod = data->m_RPCClassMethod;
                    secondData->m_turn = data->m_turn;
                    secondData->m_requestingPlayerID = data->m_requestingPlayerID;
                    secondData->m_Skill = data->m_Skill;
                    newEvent.data = secondData;
                    delete data;
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
                    //Temp hack
                    RPCBasicDiplomaticResponseStruct* secondData = new RPCBasicDiplomaticResponseStruct;
                    secondData->m_RPCClassMethod = data->m_RPCClassMethod;
                    secondData->m_turn = data->m_turn;
                    secondData->m_requestingPlayerID = data->m_requestingPlayerID;
                    secondData->m_otherPlayerId = data->m_otherPlayerId;
                    secondData->m_response = data->m_response;
                    newEvent.data = secondData;
                    delete data;
                    break;
                }
                default:
                    assert(false && "You must cast your new RPCStruct type here");
                    break;
            }

            m_queue->push(newEvent);
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