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
#include "UnitSwordsmanI.h"

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

shared_ptr<Map> WorldState::GetMapCopy()
{
    lock_guard<recursive_mutex> lock{ m_mutex };
    return shared_ptr<Map> { m_map->Clone() };
}

std::shared_ptr<Player> WorldState::GetPlayer(int playerID)
{
    return m_players.at(playerID);
}

shared_ptr<Player> WorldState::GetPlayerCopy(int playerID)
{
    lock_guard<recursive_mutex> lock{ m_mutex };
    return m_players.at(playerID)->Clone();
}

std::vector<std::shared_ptr<Player> > WorldState::GetPlayersCopy()
{
    lock_guard<recursive_mutex> lock{ m_mutex };
    std::vector<std::shared_ptr<Player> > players;

    for (auto p : m_players)
    {
        players.emplace_back(p->Clone());
    }
    return players;
}

std::vector<std::shared_ptr<Player> > WorldState::GetPlayers()
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

    //Notify players of a new turn
    for (auto player : m_players)
    {
        player->NotifyNewTurn(m_turn, m_map);

        for (auto relation : player->GetDiplomaticRelations())
        {
            if (relation.second.GetRelationStatus() == RelationStatus::Alliance)
            {
                dynamic_cast<MapLocal*>(m_map)->ShareVision(player->GetPlayerID(), relation.first);
            }
        }
    }

    //Notify map of a new turn
    m_map->NotifyNewTurn(m_turn);

}

int WorldState::AddPlayer(std::string playerName)
{
    lock_guard<recursive_mutex> lock{ m_mutex };

    for (auto player : m_players)
    {
        if (playerName == player->GetPlayerName())
        {
            if (player->IsDisconnected())
            {
                //it's a reconnect
                player->SetIsDisconnected(false);
                return player->GetPlayerID();
            }
            else
            {
                return -1;
            }
        }
    }

    if (m_players.size() == 8)
    {
        return -1;
    }

    int playerID = static_cast<int>(m_players.size());
    std::shared_ptr<Player> newPlayer = std::shared_ptr<Player>{ new PlayerLocal() };
    newPlayer->SetPlayerID(playerID);
    newPlayer->SetPlayerName(playerName);

    for (auto p : m_players)
    {
        p->AddNewRelation(playerID);
        newPlayer->AddNewRelation(p->GetPlayerID());
    }
    m_players.push_back(newPlayer);

    Position spawnPosition = m_map->GetSpawnPositions()[playerID];
    m_map->CreateDistrict(DistrictCityCenter::DISTRICT_TYPE, spawnPosition, playerID, false);
    m_map->CreateUnit(UnitSwordsmanI::UNIT_TYPE, spawnPosition, playerID, false);
    
    return playerID;
}

void WorldState::RemovePlayer(int id)
{
    lock_guard<recursive_mutex> lock{ m_mutex };
    for (auto player : m_players)
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
    for (auto player : m_players)
    {
        playerListNode.add_child("P", player->Serialize());
    }

    // Get Map XML
    worldStateNode.add_child("M", m_map->Serialize());

    return worldStateXml;
}

void WorldState::Deserialize(boost::property_tree::ptree worldStateXml, int playerID)
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

    if (m_remote)
    {
        dynamic_cast<MapRemote*>(m_map)->VisionChange(m_players[playerID]);
    }
}

void WorldState::DeserializePlayer(boost::property_tree::ptree playerXml, int playerID)
{
    lock_guard<recursive_mutex> lock{ m_mutex };
    auto playerNode = playerXml.get_child("P");
    if (m_remote)
    {
        auto player = PlayerRemote::Deserialize(playerNode);
        m_players[player->GetPlayerID()] = player;
    }
    else
    {
        auto player = PlayerLocal::Deserialize(playerNode);
        m_players[player->GetPlayerID()] = player;
    }

    if (m_remote)
    {
        dynamic_cast<MapRemote*>(m_map)->VisionChange(m_players[playerID]);
    }
}

void WorldState::DeserializeTile(boost::property_tree::ptree tileXml, int playerID)
{
    lock_guard<recursive_mutex> lock{ m_mutex };
    auto tileNode = tileXml.get_child("T");
    m_map->DeserializeTile(tileNode);

    if (m_remote)
    {
        dynamic_cast<MapRemote*>(m_map)->VisionChange(m_players[playerID]);
    }
}

std::set<Position> WorldState::MoveUnit(int ownerID, Position unitLocation, Position newLocation, int actionCost)
{
    lock_guard<recursive_mutex> lock{ m_mutex };
    return m_map->MoveUnit(ownerID, unitLocation, newLocation, actionCost);
}

std::set<Position> WorldState::Attack(int ownerID, Position attackerPosition, Position targetPosition, int actionCost)
{
    lock_guard<recursive_mutex> lock{ m_mutex };
    return m_map->Attack(ownerID, attackerPosition, targetPosition, actionCost);
}

std::set<Position> WorldState::CreateUnit(int unitType, Position pos, int owner)
{
    lock_guard<recursive_mutex> lock{ m_mutex };
    return m_map->CreateUnit(unitType, pos, owner, false);
}

std::set<Position> WorldState::CreateDistrict(int districtType, Position pos, int owner)
{
    lock_guard<recursive_mutex> lock{ m_mutex };
    return m_map->CreateDistrict(districtType, pos, owner, false);
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

std::set<Position> WorldState::UpgradeUnit(Position pos, int ownerId)
{
    lock_guard<recursive_mutex> lock{ m_mutex };
    return m_map->UpgradeUnit(pos, ownerId);
}

std::set<Position> WorldState::UpgradeDistrict(Position pos, int ownerId)
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

    for (auto player : m_players)
    {
        if (player->IsAlive() && !player->IsPlayerReadyForNextTurn())
        {
            return false;
        }
    }

    return true;
}