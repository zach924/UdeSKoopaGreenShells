#include "Player.h"
#include "GameSession.h"

int Player::playerIDCounter = 0;

Player::Player()
   :m_playerID(playerIDCounter++),
    m_isReadyForNewTurn(false),
    m_isAlive(true),
    m_cityHallCount(0), // TODO : Be sure we will have one City Hall when game start
    m_unitCount(0), 
    m_food(100), 
    m_science(0),
    m_weapon(0),
    m_foodMultiplier(1), 
    m_scienceMultiplier(1), 
    m_weaponMultiplier(1)
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

int Player::GetFood()
{
    return m_food;
}

int Player::GetScience()
{
    return m_science;
}

int Player::GetWeapon()
{
    return m_weapon;
}

void Player::AddFood(unsigned int qty)
{
    m_food += static_cast<unsigned int>(qty * m_foodMultiplier);
}

void Player::AddScience(unsigned int qty)
{
    m_science += static_cast<unsigned int>(qty * m_scienceMultiplier);
}

void Player::AddWeapon(unsigned int qty)
{
    m_weapon += static_cast<unsigned int>(qty * m_weaponMultiplier);
}

bool Player::ConsumeFood(unsigned int qty)
{
    bool enoughtRessource = m_food >= qty;

    if (enoughtRessource)
    {
        m_food -= qty;
    }
    return enoughtRessource;
}

bool Player::ConsumeScience(unsigned int qty)
{
    bool enoughtRessource = m_science >= qty;

    if (enoughtRessource)
    {
        m_science -= qty;
    }
    return enoughtRessource;
}

bool Player::ConsumeWeapon(unsigned int qty)
{
    bool enoughtRessource = m_weapon >= qty;

    if (enoughtRessource)
    {
        m_weapon -= qty;
    }
    return enoughtRessource;
}

void Player::AddFoodMultiplier(double multiplier)
{
    m_foodMultiplier += multiplier;
}

void Player::AddScienceMultiplier(double multiplier)
{
    m_scienceMultiplier += multiplier;
}

void Player::AddWeaponMultiplier(double multiplier)
{
    m_weaponMultiplier += multiplier;
}

void Player::RemoveFoodMultiplier(double multiplier)
{
    // no unsigned double so valid we dont go under 0
    if (m_foodMultiplier >= multiplier)
    {
        m_foodMultiplier -= multiplier;
    }
    else
    {
        m_foodMultiplier = 0.0;
    }
}

void Player::RemoveScienceMultiplier(double multiplier)
{
    // no unsigned double so valid we dont go under 0
    if (m_scienceMultiplier >= multiplier)
    {
        m_scienceMultiplier -= multiplier;
    }
    else
    {
        m_scienceMultiplier = 0.0;
    }
}

void Player::RemoveWeaponMultiplier(double multiplier)
{
    // no unsigned double so valid we dont go under 0
    if (m_weaponMultiplier >= multiplier)
    {
        m_weaponMultiplier -= multiplier;
    }
    else
    {
        m_weaponMultiplier = 0.0;
    }
}

bool Player::IsAlive()
{
	return m_isAlive;
}
