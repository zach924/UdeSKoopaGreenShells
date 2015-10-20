#include "Player.h"
#include "GameSession.h"
#include <boost\property_tree\ptree.hpp>

Player::Player()
   :m_playerID(),
    m_playerName(),
    m_isReadyForNewTurn(false),
    m_isAlive(true),
    m_cityCenterCount(0), // TODO : Be sure we will have one City Hall when game start
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

void Player::AddCityCenter()
{
	++m_cityCenterCount;
}

void Player::RemoveCityCenter()
{
	--m_cityCenterCount;

	if (m_cityCenterCount <= 0)
	{
		m_isAlive = false;
	}
}

bool Player::IsAlive()
{
	return m_isAlive;
}

boost::property_tree::ptree Player::Serialize()
{
    boost::property_tree::ptree playerNode;
    playerNode.put("<xmlattr>.PId", m_playerID);
    playerNode.put("<xmlattr>.PName", m_playerName);
    playerNode.put("<xmlattr>.CHC", m_cityCenterCount);
    playerNode.put("<xmlattr>.UC", m_unitCount);
    playerNode.put("<xmlattr>.F", m_food);
    playerNode.put("<xmlattr>.S", m_science);
    playerNode.put("<xmlattr>.W", m_weapon);
    playerNode.put("<xmlattr>.FM", m_foodMultiplier);
    playerNode.put("<xmlattr>.SM", m_scienceMultiplier);
    playerNode.put("<xmlattr>.WM", m_weaponMultiplier);

    return playerNode;
}

Player Player::Deserialize(boost::property_tree::ptree playerNode)
{
    Player player;

    player.m_playerID = playerNode.get<int>("<xmlattr>.PId");
    player.m_playerName = playerNode.get<std::string>("<xmlattr>.PName");
    player.m_cityCenterCount = playerNode.get<int>("<xmlattr>.CHC");
    player.m_unitCount = playerNode.get<int>("<xmlattr>.UC");
    player.m_food = playerNode.get<int>("<xmlattr>.F");
    player.m_science = playerNode.get<int>("<xmlattr>.S");
    player.m_weapon = playerNode.get<int>("<xmlattr>.W");
    player.m_foodMultiplier = playerNode.get<double>("<xmlattr>.FM");
    player.m_scienceMultiplier = playerNode.get<double>("<xmlattr>.SM");
    player.m_weaponMultiplier = playerNode.get<double>("<xmlattr>.WM");

    return player;
}
