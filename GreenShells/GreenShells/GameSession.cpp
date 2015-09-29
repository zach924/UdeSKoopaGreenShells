#include <string>
#include <iostream>
#include "GameSession.h"
#include "Player.h"
#include "RPCManager.h"
#include "RPCBase.h"
#include "RPCDispatcher.h"

GameSession::GameSession()
:m_worldState(),
m_serverIP(),
m_allPLayerReady(false)
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

