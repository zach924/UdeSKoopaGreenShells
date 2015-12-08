#include <string>
#include <iostream>
#include "GameSession.h"
#include "Player.h"
#include "RPCManager.h"
#include "RPCBase.h"
#include "RPCDispatcher.h"
#include "RPCStructs.h"
#include "SelectionManager.h"

#include <boost\property_tree\ptree.hpp>
#include <boost\property_tree\xml_parser.hpp>
#include <boost\filesystem.hpp>
#include <iostream>
#include <fstream>
#include <exception>

GameSession::GameSession()
    :m_worldState(true), m_serverIP(), m_currentPlayerID(-1)
{
}

GameSession::~GameSession()
{
}

WorldState * GameSession::GetWorldState()
{
    return &m_worldState;
}

void GameSession::SetServerIP(std::string ip)
{
    m_serverIP = ip;
}

std::string GameSession::GetServerIP()
{
    return m_serverIP;
}

void GameSession::SetPort(int port)
{
    m_port = port;
}

int GameSession::GetPort()
{
    return m_port;
}

int GameSession::GetCurrentPlayerID()
{
    return m_currentPlayerID;
}

void GameSession::SetCurrentPlayerID(int player)
{
    m_currentPlayerID = player;
}

std::shared_ptr<Player> GameSession::GetCurrentPlayerCopy()
{
    return  m_worldState.GetPlayerCopy(m_currentPlayerID);
}

bool GameSession::ConnectToServer(char* playerName)
{
    bool result = RPCBase::EstablishConnection(m_serverIP, std::to_string(m_port));

    std::stringstream ss;
    PlayerInfoStruct nameToSend;
    nameToSend.setPlayerName(playerName);
    ss.write(reinterpret_cast<char*>(&nameToSend), sizeof(nameToSend));
    RPCBase::GetConnection()->GetSocket().send(boost::asio::buffer(ss.str()));

    PlayerInfoStruct* data = new PlayerInfoStruct();
    RPCBase::GetConnection()->GetSocket().receive(boost::asio::buffer(reinterpret_cast<char*>(data), sizeof(PlayerInfoStruct)));
    m_currentPlayerID = data->playerID;
    delete data;
    //First Replication
    FetchReplication();

    m_replicationThread = new std::thread(&GameSession::FetchReplicationThread, this);
    return result;
}

void GameSession::Save(std::string fileName)
{
    boost::filesystem::path saveDir("Saves");
   
    try
    {
        boost::filesystem::create_directory(saveDir);
    }
    catch (exception e)
    {
        std::cout << "Can't create the directory for saved file." << endl;
        std::cout << e.what() << std::endl;
    }

    std::ofstream fileStream;
    fileName.insert(0, "Saves\\");
    fileName += ".xml";
    fileStream.open(fileName);

    if (fileStream.good())
    {
        boost::property_tree::write_xml(fileStream, m_worldState.Serialize());
    }

    fileStream.close();
}

void GameSession::Load(std::string fileName)
{
    std::ifstream fileStream;
    fileStream.open(fileName);

    if (fileStream)
    {
        try
        {
            boost::property_tree::ptree pt;
            boost::property_tree::xml_parser::read_xml(fileStream, pt);
            m_worldState.Deserialize(pt, m_currentPlayerID);

            fileStream.close();
        }
        catch (const std::exception& e)
        {
            std::cout << e.what() << std::endl;
        }
    }
    else
    {
        std::string msg = ("Unable to load saved file %s!", fileName);
        throw new std::exception(msg.c_str());
    }
}

void GameSession::FetchReplication()
{
    ReplicationType type;
    RPCBase::GetConnection()->GetSocket().receive(boost::asio::buffer(reinterpret_cast<char*>(&type), sizeof(ReplicationType)));

    int theoreticalSize{ 0 };
    RPCBase::GetConnection()->GetSocket().receive(boost::asio::buffer(reinterpret_cast<char*>(&theoreticalSize), sizeof(int)));

    int actualSize = 0;
    stringstream dataStream;
    while (actualSize != theoreticalSize)
    {
        char* data = new char[theoreticalSize - actualSize];
        int receivedSize = static_cast<int>(RPCBase::GetConnection()->GetSocket().receive(boost::asio::buffer(data, theoreticalSize - actualSize)));
        dataStream.write(data, receivedSize);
        delete data;
        actualSize += receivedSize;
    }
    boost::property_tree::ptree pt;
    boost::property_tree::xml_parser::read_xml(dataStream, pt);

    switch (type)
    {
    case WORLDSTATE:
        m_worldState.Deserialize(pt, m_currentPlayerID);
        break;
    case PLAYER:
        m_worldState.DeserializePlayer(pt, m_currentPlayerID);
        break;
    case TILE:
        m_worldState.DeserializeTile(pt, m_currentPlayerID);
        break;
    default:
        assert(false && "Insert replication type here");
        break;
    }

    SelectionManager::GetInstance().UpdateButtonState();
}

void GameSession::FetchReplicationThread()
{
    try
    {
        while (true)
        {
            FetchReplication();
        }
    }
    catch (std::exception e)
    {
        std::cout << "Replication error : Closing replication thread." << endl;
        std::cout << e.what() << std::endl;
    }
}