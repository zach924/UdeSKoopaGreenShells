#include <string>
#include <iostream>
#include "GameSession.h"
#include "Player.h"
#include "RPCManager.h"
#include "RPCBase.h"
#include "RPCDispatcher.h"

#include <boost\property_tree\ptree.hpp>
#include <boost\property_tree\xml_parser.hpp>
#include <iostream>
#include <fstream>
#include <exception>

GameSession::GameSession()
:m_worldState(),
m_serverIP()
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

bool GameSession::ConnectToServer()
{
	bool result = RPCBase::EstablishConnection(m_serverIP, std::to_string(m_port));
	RPCStructType newEvent{};
	RPCBase::GetConnection()->GetSocket().receive(boost::asio::buffer(reinterpret_cast<char*>(&newEvent), sizeof(RPCStructType)));

	JoinGameStruct* data = new JoinGameStruct;
	RPCBase::GetConnection()->GetSocket().receive(boost::asio::buffer(reinterpret_cast<char*>(data), sizeof(JoinGameStruct)));
	m_currentPlayerID = data->playerID;

	//First Replication
	FetchReplication();

	m_replicationThread = new std::thread(&GameSession::FetchReplicationThread, this);
	return result;
}

void GameSession::Save(std::string fileName)
{
    std::ofstream fileStream;
    fileStream.open(fileName);

    boost::property_tree::write_xml(fileStream, m_worldState.Serialize(), boost::property_tree::xml_writer_settings<std::string>('\t', 1));

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
			m_worldState.Deserialize(pt);

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
	int theoreticalSize{0};
	RPCBase::GetConnection()->GetSocket().receive(boost::asio::buffer(reinterpret_cast<char*>(&theoreticalSize), sizeof(int)));

	int actualSize = 0;
	stringstream dataStream;
	while (actualSize != theoreticalSize)
	{
		char* data = new char[theoreticalSize - actualSize];
		int receivedSize = static_cast<int>(RPCBase::GetConnection()->GetSocket().receive(boost::asio::buffer(data, theoreticalSize - actualSize)));
		dataStream.write(data, receivedSize);
		actualSize += receivedSize;
	}
	boost::property_tree::ptree pt;
	boost::property_tree::xml_parser::read_xml(dataStream, pt);
	m_worldState.Deserialize(pt);
	std::cout << "Replication has occured." << std::endl;
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

