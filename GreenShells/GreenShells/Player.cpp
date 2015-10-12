#include "Player.h"
#include "GameSession.h"
#include <boost\property_tree\ptree.hpp>

int Player::playerIDCounter = 0;

Player::Player()
   :m_playerID(playerIDCounter++),
    m_playerName(),
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
	++m_cityHallCount;
}

void Player::RemoveCityCenter()
{
	--m_cityHallCount;

	if (m_cityHallCount <= 0)
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
    playerNode.put("<xmlattr>.PlayerId", m_playerID);
    playerNode.put("<xmlattr>.PlayerName", m_playerName);
    playerNode.put("<xmlattr>.CityHallCount", m_cityHallCount);
    playerNode.put("<xmlattr>.UnitCount", m_unitCount);
    playerNode.put("<xmlattr>.Food", m_food);
    playerNode.put("<xmlattr>.Science", m_science);
    playerNode.put("<xmlattr>.Weapon", m_weapon);
    playerNode.put("<xmlattr>.FoodMultiplicator", m_foodMultiplier);
    playerNode.put("<xmlattr>.ScienceMultiplicator", m_scienceMultiplier);
    playerNode.put("<xmlattr>.WeaponMultiplicator", m_weaponMultiplier);

    return playerNode;
}

Player Player::Deserialize(boost::property_tree::ptree playerNode)
{
    Player player;

    player.m_playerID = playerNode.get<int>("<xmlattr>.PlayerId");
    player.m_playerName = playerNode.get<std::string>("<xmlattr>.PlayerName");
    player.m_cityHallCount = playerNode.get<int>("<xmlattr>.CityHallCount");
    player.m_unitCount = playerNode.get<int>("<xmlattr>.UnitCount");
    player.m_food = playerNode.get<int>("<xmlattr>.Food");
    player.m_science = playerNode.get<int>("<xmlattr>.Science");
    player.m_weapon = playerNode.get<int>("<xmlattr>.Weapon");
    player.m_foodMultiplier = playerNode.get<double>("<xmlattr>.FoodMultiplicator");
    player.m_scienceMultiplier = playerNode.get<double>("<xmlattr>.ScienceMultiplicator");
    player.m_weaponMultiplier = playerNode.get<double>("<xmlattr>.WeaponMultiplicator");

    return player;
}
