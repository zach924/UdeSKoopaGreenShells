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
	return RPCBase::EstablishConnection(m_serverIP, std::to_string(m_port));
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
		boost::property_tree::ptree pt;
		boost::property_tree::xml_parser::read_xml(fileStream, pt);
		m_worldState = WorldState::Deserialize(pt);

		fileStream.close();
	}
	else
	{
		std::string msg = ("Unable to load saved file %s!", fileName);
		throw new std::exception(msg.c_str());
	}
}

