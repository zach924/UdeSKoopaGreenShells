#include "Player.h"
#include "Unit.h"
#include "District.h"

Player::Player()
:m_isReadyForNewTurn(true),
//m_isAlive(true),
m_units(), m_districts()
{
}


Player::~Player()
{
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
