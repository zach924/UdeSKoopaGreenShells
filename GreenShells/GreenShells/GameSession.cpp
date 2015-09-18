#include "GameSession.h"
#include "WorldState.h"

GameSession::GameSession()
:m_worldState()
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
