#include "GameSession.h"
#include "Player.h"

#include <boost\property_tree\ptree.hpp>
#include <boost\property_tree\xml_parser.hpp>
#include <iostream>
#include <fstream>

GameSession::GameSession()
:m_worldState(),
m_serverIP()
{
}


GameSession::~GameSession()
{
	
}

void GameSession::SetIsServer(bool isServer)
{
	m_isServer = isServer;
}

bool GameSession::IsServer()
{
	return m_isServer;
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

int GameSession::getPort()
{
	return m_port;
}

void GameSession::PrepareGame()
{
	m_worldState.PrepareGame();
}

WorldState GameSession::GetWorldState()
{
    return m_worldState;
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

    boost::property_tree::ptree pt;
    boost::property_tree::xml_parser::read_xml(fileStream, pt);
    m_worldState = WorldState::Deserialize(pt);

    fileStream.close();
}

