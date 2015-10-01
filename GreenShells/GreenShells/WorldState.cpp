#include <algorithm>

#include "WorldState.h"
#include "Player.h"
#include "MapLocal.h"

#include <boost\property_tree\ptree.hpp>

WorldState::WorldState()
:m_map(nullptr), m_players()
{
	
}

WorldState::~WorldState()
{
}

void WorldState::SetMap(Map* map)
{
	m_map = map;
}

Map* WorldState::GetMap()
{
	return m_map;
}

void WorldState::PrepareGame()
{
	m_map =	new MapLocal();
	m_map->GenerateTiles();
}

int WorldState::GetCurrentTurn()
{
	return m_turn;
}

void WorldState::NotifyNewTurn()
{
	m_turn++;

	//Notify map of a new turn
	m_map->NotifyNewturn();

	//Notify players of a new turn
	for (Player& player : m_players)
	{
		if(player.IsAlive())
		{
			player.NotifyNewTurn();
		}
	}
}

void WorldState::AddPlayer(const Player& player)
{
	m_players.emplace_back(player);
}

void WorldState::RemovePlayer(int id)
{
    for (Player &player : m_players)
    {
        if (player.GetPlayerID() == id)
        {
			player.SetDead();
            break;
        }
    }
}

boost::property_tree::ptree WorldState::Serialize()
{
    boost::property_tree::ptree worldStateXml;

    boost::property_tree::ptree& worldStateNode = worldStateXml.add("WorldState", "");

    // Get Player XML to add here
    boost::property_tree::ptree& playerListNode = worldStateNode.add("Players", "");
    for (Player player : m_players)
    {
        playerListNode.add_child("Player", player.Serialize());
    }

    // Get Map XML
    worldStateNode.add_child("Map", m_map->Serialize());
    
    return worldStateXml;
}

WorldState WorldState::Deserialize(boost::property_tree::ptree worldStateXml)
{
    WorldState worldState;

    for each (auto worldStateNode in worldStateXml.get_child("WorldState"))
    {
        if (worldStateNode.first == "Players")
        {
            for each (auto playerNode in worldStateNode.second)
            {
                worldState.AddPlayer(Player::Deserialize(playerNode.second));
            }
        }
        else if (worldStateNode.first == "Map")
        {
            worldState.m_map = MapLocal::Deserialize(worldStateNode.second);
			// TODO :  need to know from wich class we need to Deserialize, cause map is abstract (bool in WorldState)
        }

    }

    return worldState;
}

Player & WorldState::GetPlayer(int playerID)
{
	return m_players.at(playerID);
}

bool WorldState::AreAllPlayerReady()
{
	if (m_players.empty())
	{
		return false;
	}

	for (Player& player : m_players)
	{
		if (player.IsAlive() && !player.IsPlayerReadyForNextTurn())
		{
			return false;
		}
	}

	return true;
}