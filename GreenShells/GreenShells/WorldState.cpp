#include <algorithm>

#include "WorldState.h"
#include "Player.h"

#include <boost\property_tree\ptree.hpp>

WorldState::WorldState()
:m_map(), m_players()
{
    m_map.GenerateTiles();
}

WorldState::~WorldState()
{
}

void WorldState::PrepareGame()
{
    AddPlayer(Player());
}

void WorldState::AddPlayer(const Player& player)
{
    m_players.push_back(player);
}

void WorldState::RemovePlayer(int id)
{
    for (Player &player : m_players)
    {
        if (player.GetPlayerID() == id)
        {
            player.SetPlayerDead();
            break;
        }
    }
}

Map WorldState::GetMap()
{
    return m_map;
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
    worldStateNode.add_child("Map", m_map.Serialize());
    
    return worldStateXml;
}

//void WorldState::Deserialize(boost::property_tree::ptree worldStateXml)
//{
//    for each (auto worldStateNode in worldStateXml.get_child("WorldState"))
//    {
//        if (worldStateNode.first == "Players")
//        {
//            int i = 0;
//            for each (auto playerNode in worldStateNode.second)
//            {
//                m_players[i].Deserialize(playerNode.second);
//            }
//        }
//        else if (worldStateNode.first == "Map")
//        {
//            m_map.Deserialize(worldStateNode.second);
//        }
//
//    }
//}
