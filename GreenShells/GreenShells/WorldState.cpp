#include <algorithm>
#include <iostream>
#include <boost\property_tree\ptree.hpp>

#include "WorldState.h"
#include "Player.h"
#include "PlayerLocal.h"
#include "PlayerRemote.h"
#include "Map"
#include "MapLocal.h"
#include "MapRemote.h"
#include "TileBase.h"
#include "DistrictCityCenter.h"

using namespace std;

WorldState::WorldState(bool isRemote)
    :m_map(nullptr), m_players(), m_mutex(), m_turn(1), m_remote(isRemote)
{
}

WorldState::~WorldState()
{
    delete m_map;
}

Map* WorldState::GetMap()
{
    return m_map;
}

Map* WorldState::GetMapCopy()
{
    lock_guard<recursive_mutex> lock{ m_mutex };
    return m_map->Clone();
}

Player* WorldState::GetPlayer(int playerID)
{
    return m_players.at(playerID);
}

shared_ptr<Player> WorldState::GetPlayerCopy(int playerID)
{
    lock_guard<recursive_mutex> lock{ m_mutex };
    return shared_ptr<Player> { m_players.at(playerID)->Clone() };
}

std::vector<Player*> WorldState::GetPlayersCopy()
{
    lock_guard<recursive_mutex> lock{ m_mutex };
    std::vector<Player*> players;

    for (auto p : m_players)
    {
        players.emplace_back(p->Clone());
    }
    return players;
}

std::vector<Player*> WorldState::GetPlayers()
{
    return m_players;
}

void WorldState::PrepareLocalGame()
{
    lock_guard<recursive_mutex> lock{ m_mutex };
    m_map = new MapLocal();
    m_map->GenerateTiles();
}

int WorldState::GetCurrentTurn()
{
    lock_guard<recursive_mutex> lock{ m_mutex };
    return m_turn;
}

void WorldState::NotifyNewTurn()
{
    lock_guard<recursive_mutex> lock{ m_mutex };
    m_turn++;

    //Notify map of a new turn
    m_map->NotifyNewTurn(m_turn);

    //Notify players of a new turn
    for (Player* player : m_players)
    {
        player->NotifyNewTurn(m_turn, m_map);
    }
}

int WorldState::AddPlayer(std::string playerName)
{
    lock_guard<recursive_mutex> lock{ m_mutex };

    for (auto player : m_players)
    {
        if (playerName == player->GetPlayerName())
        {
            //it's a reconnect
            std::cout << playerName << " has reconnected!" << endl;
            player->SetIsDisconnected(false);
            return player->GetPlayerID();
        }
    }

    int playerID = static_cast<int>(m_players.size());
    std::cout << playerName << " has joined and his id is " << playerID << endl;
    Player* newPlayer = new PlayerLocal();
    newPlayer->SetPlayerID(playerID);
    newPlayer->SetPlayerName(playerName);

    newPlayer->AddScience(1000000);
    newPlayer->AddWeapon(100000);
    for (auto p : m_players)
    {
        p->AddNewRelation(playerID);
        newPlayer->AddNewRelation(p->GetPlayerID());
    }
    m_players.push_back(newPlayer);

    Position spawnPosition = m_map->GetSpawnPositions()[playerID];
    m_map->CreateDistrict(DistrictCityCenter::DISTRICT_TYPE, spawnPosition, playerID);
    
    return playerID;
}

void WorldState::RemovePlayer(int id)
{
    lock_guard<recursive_mutex> lock{ m_mutex };
    for (Player* player : m_players)
    {
        if (player->GetPlayerID() == id)
        {
            player->SetIsAlive(false);
            break;
        }
    }
}

boost::property_tree::ptree WorldState::Serialize()
{
    lock_guard<recursive_mutex> lock{ m_mutex };
    boost::property_tree::ptree worldStateXml;

    boost::property_tree::ptree& worldStateNode = worldStateXml.add("WS", "");
    worldStateNode.put("<xmlattr>.Turn", m_turn);

    // Get Player XML to add here
    boost::property_tree::ptree& playerListNode = worldStateNode.add("Ps", "");
    for (Player* player : m_players)
    {
        playerListNode.add_child("P", player->Serialize());
    }

    // Get Map XML
    worldStateNode.add_child("M", m_map->Serialize());

    return worldStateXml;
}

void WorldState::Deserialize(boost::property_tree::ptree worldStateXml)
{
    lock_guard<recursive_mutex> lock{ m_mutex };

    m_players.clear();
    delete m_map;
    auto WS = worldStateXml.get_child("WS");
    m_turn = WS.get<int>("<xmlattr>.Turn");

    for each (auto worldStateNode in WS)
    {
        if (worldStateNode.first == "Ps")
        {
            if (m_remote)
            {
                for each (auto playerNode in worldStateNode.second)
                {
                    m_players.push_back(PlayerRemote::Deserialize(playerNode.second));
                }
            }
            else
            {
                for each (auto playerNode in worldStateNode.second)
                {
                    m_players.push_back(PlayerLocal::Deserialize(playerNode.second));
                }
            }
        }
        else if (worldStateNode.first == "M")
        {
            if (m_remote)
            {
                m_map = MapRemote::Deserialize(worldStateNode.second);
            }
            else
            {
                m_map = MapLocal::Deserialize(worldStateNode.second);
            }
        }
    }
}

bool WorldState::MoveUnit(int ownerID, Position unitLocation, Position newLocation)
{
    lock_guard<recursive_mutex> lock{ m_mutex };
    return m_map->MoveUnit(ownerID, unitLocation, newLocation);
}

bool WorldState::Attack(int ownerID, Position attackerPosition, Position targetPosition)
{
    lock_guard<recursive_mutex> lock{ m_mutex };
    return m_map->Attack(ownerID, attackerPosition, targetPosition);
}

bool WorldState::CreateUnit(int unitType, Position pos, int owner)
{
    lock_guard<recursive_mutex> lock{ m_mutex };
    return m_map->CreateUnit(unitType, pos, owner);
}

bool WorldState::CreateDistrict(int districtType, Position pos, int owner)
{
    lock_guard<recursive_mutex> lock{ m_mutex };
    return m_map->CreateDistrict(districtType, pos, owner);
}

bool WorldState::SellUnit(Position pos, int ownerId)
{
    lock_guard<recursive_mutex> lock{ m_mutex };
    return m_map->SellUnit(pos, ownerId);
}

bool WorldState::SellDistrict(Position pos, int ownerId)
{
    lock_guard<recursive_mutex> lock{ m_mutex };
    return m_map->SellDistrict(pos, ownerId);
}

bool WorldState::UpgradeUnit(Position pos, int ownerId)
{
    lock_guard<recursive_mutex> lock{ m_mutex };
    return m_map->UpgradeUnit(pos, ownerId);
}

bool WorldState::UpgradeDistrict(Position pos, int ownerId)
{
    lock_guard<recursive_mutex> lock{ m_mutex };
    return m_map->UpgradeDistrict(pos, ownerId);
}

bool WorldState::HealUnit(Position pos, int ownerId)
{
    lock_guard<recursive_mutex> lock{ m_mutex };
    return m_map->HealUnit(pos, ownerId);
}

bool WorldState::RepairDistrict(Position pos, int ownerId)
{
    lock_guard<recursive_mutex> lock{ m_mutex };
    return m_map->RepairDistrict(pos, ownerId);
}

bool WorldState::AreAllPlayerReady()
{
    lock_guard<recursive_mutex> lock{ m_mutex };
    if (m_players.empty())
    {
        return false;
    }

    for (Player* player : m_players)
    {
        if (player->IsAlive() && !player->IsPlayerReadyForNextTurn())
        {
            return false;
        }
    }

    return true;
}