#include "Player.h"
#include "GameSession.h"

int Player::playerIDCounter = 0;

Player::Player()
:m_playerID(playerIDCounter++),
m_isReadyForNewTurn(false),
m_isAlive(true),
m_units(), m_districts()
{
}


Player::~Player()
{
}

int Player::GetPlayerID()
{
	return m_playerID;
}

void Player::NotifyNewTurn()
{
	m_isReadyForNewTurn = false;
}

void Player::SetPlayerReadyForNextTurn(bool isReady)
{
	m_isReadyForNewTurn = isReady;
	if (m_isReadyForNewTurn)
	{
		GameSession::GetInstance().NotifyPlayerReadyForNewTurn();
	}

}

bool Player::IsPlayerReadyForNextTurn()
{
	return m_isReadyForNewTurn;
}

void Player::SetDead()
{
	m_isAlive = false;
}

bool Player::IsAlive()
{
	return m_isAlive;
}
