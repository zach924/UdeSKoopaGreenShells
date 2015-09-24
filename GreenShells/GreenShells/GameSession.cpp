#include "GameSession.h"
#include "Player.h"

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
