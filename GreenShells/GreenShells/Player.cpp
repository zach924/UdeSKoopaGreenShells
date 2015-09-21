#include "Player.h"

int Player::playerIDCounter = 0;

Player::Player()
:m_playerID(playerIDCounter++),
m_isReadyForNewTurn(true),
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

void Player::SetPlayerReadyForNextTurn()
{
	m_isReadyForNewTurn = true;
}

bool Player::IsPlayerReadyForNextTurn()
{
	return m_isReadyForNewTurn;
}

void Player::SetPlayerDead()
{
	m_isAlive = false;
}
