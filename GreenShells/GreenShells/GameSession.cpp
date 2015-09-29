#include <string>
#include <iostream>
#include "GameSession.h"
#include "Player.h"
#include "RPCManager.h"
#include "RPCBase.h"

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

int GameSession::GetPort()
{
	return m_port;
}

bool GameSession::ConnectToServer()
{
	return RPCBase::EstablishConnection(m_serverIP, std::to_string(m_port));;
}

void GameSession::PrepareGame()
{
	m_worldState.PrepareGame();
	m_rpcServerManager = new RPCManager(m_port);
	m_rpcServerManager->StartListening();
}

void GameSession::RunGame()
{
	m_gameSessionThread = std::thread(&GameSession::Run, this);
}

void GameSession::Run()
{
	// Todo: one winner
	while (true)
	{
		// Notify world sate of a new turn
		m_worldState.NotifyNewTurn();

		//End of turn when every player is ready
		while (!m_worldState.IsAllPlayerReady())
		{
			// Todo: dispatch stuff
			//std::cout << "Unlocking" << std::endl;
		}

	}
}

void GameSession::QuitGame()
{
	m_gameSessionThread.join();
}


