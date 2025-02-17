#include <sstream>
#include "MapRemote.h"
#include "RPCStructs.h"
#include "GameSession.h"
#include "Player.h"

#include "DistrictBase.h"
#include "UnitBase.h"

#include "TileGround.h"
#include "TileMountain.h"
#include "TileWater.h"
#include <boost\property_tree\ptree.hpp>

#include <iostream>

MapRemote::MapRemote()
    :Map()
{
}

MapRemote::~MapRemote()
{
}


void MapRemote::VisionChange(std::shared_ptr<Player> player)
{
    set<int> playerIDsCanSee;
    playerIDsCanSee.insert(player->GetPlayerID());
    auto relations = player->GetDiplomaticRelations();

    for (auto relation : relations)
    {
        if (relation.second.GetRelationStatus() == RelationStatus::Alliance)
        {
            playerIDsCanSee.insert(relation.first);
        }
    }
    auto utilitySK = GameSession::GetInstance().GetCurrentPlayerCopy()->GetUtilitySkillTree();
    int viewModifier = utilitySK.VisionUpgrade ? 1 : 0;

    for (int row = 0; row < ROWS; ++row)
    {
        for (int column = 0; column < COLUMNS; ++column)
        {
            m_tiles[row][column]->PlayerDontSeeAnymore(player->GetPlayerID());
        }
    }

    for (int row = 0; row < ROWS; ++row)
    {
        for (int column = 0; column < COLUMNS; ++column)
        {
            auto district = m_tiles[row][column]->GetDistrict();
            auto unit = m_tiles[row][column]->GetUnit();

            if (district)
            {
                if (playerIDsCanSee.find(district->GetOwnerID()) != playerIDsCanSee.end())
                {
                    auto positionGotVision = GetArea(Position{ column, row }, district->GetViewRange() + viewModifier, NO_FILTER, true);

                    for (const std::pair<Position, int>& pos : positionGotVision)
                    {
                        m_tiles[pos.first.Row][pos.first.Column]->PlayerSee(player->GetPlayerID());
                    }
                }
            }
            if (unit)
            {
                if (playerIDsCanSee.find(unit->GetOwnerID()) != playerIDsCanSee.end())
                {
                    auto positionGotVision = GetArea(Position{ column, row }, unit->GetViewRange() + viewModifier, NO_FILTER, true);

                    for (const std::pair<Position, int>& pos : positionGotVision)
                    {
                        m_tiles[pos.first.Row][pos.first.Column]->PlayerSee(player->GetPlayerID());
                    }
                }
            }
        }
    }
}

Map* MapRemote::Clone()
{
    MapRemote* map = new MapRemote{};

    for (auto spawn : m_spawnPositions)
    {
        map->m_spawnPositions.push_back(spawn);
    }

    for (int i = 0; i < ROWS; i++)
    {
        map->m_tiles.push_back(std::vector<TileBase*>(COLUMNS));
    }
    for (int row = 0; row < ROWS; ++row)
    {
        for (int column = 0; column < COLUMNS; ++column)
        {
            map->m_tiles[row][column] = m_tiles[row][column]->Clone();
        }
    }
    return map;
}

std::set<Position> MapRemote::MoveUnit(int ownerID, Position unitLocation, Position newLocation, int actionCost)
{
    std::stringstream ss;

    RPCStructType dataType{};
    dataType = RPCStructType::RPC_BASIC_TWO_POSITIONS_AND_COST;
    ss.write(reinterpret_cast<char*>(&dataType), sizeof(dataType));

    RPCBasicTwoPositionsAndCostStruct data;
    data.m_RPCClassMethod = RPCClassMethodType::Map_Move;
    data.m_turn = GameSession::GetInstance().GetWorldState()->GetCurrentTurn();
    data.m_requestingPlayerID = ownerID;
    data.m_firstPosition = unitLocation;
    data.m_secondPosition = newLocation;
    data.m_actionCost = actionCost;

    ss.write(reinterpret_cast<char*>(&data), sizeof(data));
    SendData(ss.str());
    return std::set<Position>{};
}

std::set<Position> MapRemote::Attack(int ownerID, Position attackerPosition, Position targetPosition, int actionCost)
{
    std::stringstream ss;

    RPCStructType dataType{};
    dataType = RPCStructType::RPC_BASIC_TWO_POSITIONS_AND_COST;
    ss.write(reinterpret_cast<char*>(&dataType), sizeof(dataType));

    RPCBasicTwoPositionsAndCostStruct data;
    data.m_RPCClassMethod = RPCClassMethodType::Map_Attack;
    data.m_turn = GameSession::GetInstance().GetWorldState()->GetCurrentTurn();
    data.m_requestingPlayerID = ownerID;
    data.m_firstPosition = attackerPosition;
    data.m_secondPosition = targetPosition;
    data.m_actionCost = actionCost;

    ss.write(reinterpret_cast<char*>(&data), sizeof(data));

    SendData(ss.str());
    return std::set<Position>{};
}

std::set<Position> MapRemote::CreateUnit(int unitType, Position pos, int owner, bool upgrade = false)
{
    std::stringstream ss;

    RPCStructType dataType{};
    dataType = RPCStructType::RPC_BASIC_CREATION;
    ss.write(reinterpret_cast<char*>(&dataType), sizeof(dataType));

    RPCBasicActorCreationStruct data;
    data.m_RPCClassMethod = RPCClassMethodType::Map_CreateUnit;
    data.m_turn = GameSession::GetInstance().GetWorldState()->GetCurrentTurn();
    data.m_requestingPlayerID = owner;
    data.m_positionToCreate = pos;
    data.m_actorType = unitType;

    ss.write(reinterpret_cast<char*>(&data), sizeof(data));

    SendData(ss.str());
    return std::set<Position>{};
}

std::set<Position> MapRemote::CreateDistrict(int districtType, Position pos, int owner, bool upgrade = false)
{
    std::stringstream ss;

    RPCStructType dataType{};
    dataType = RPCStructType::RPC_BASIC_CREATION;
    ss.write(reinterpret_cast<char*>(&dataType), sizeof(dataType));

    RPCBasicActorCreationStruct data;
    data.m_RPCClassMethod = RPCClassMethodType::Map_CreateDistrict;
    data.m_turn = GameSession::GetInstance().GetWorldState()->GetCurrentTurn();
    data.m_requestingPlayerID = owner;
    data.m_positionToCreate = pos;
    data.m_actorType = districtType;

    ss.write(reinterpret_cast<char*>(&data), sizeof(data));

    SendData(ss.str());
    return std::set<Position>{};
}

bool MapRemote::SellDistrict(Position pos, int owner)
{
    std::stringstream ss;

    RPCStructType dataType{};
    dataType = RPCStructType::RPC_BASIC_ONE_POSITION;
    ss.write(reinterpret_cast<char*>(&dataType), sizeof(dataType));

    RPCBasicOnePositionStruct data;
    data.m_RPCClassMethod = RPCClassMethodType::Map_SellDistrict;
    data.m_turn = GameSession::GetInstance().GetWorldState()->GetCurrentTurn();
    data.m_requestingPlayerID = owner;
    data.m_position = pos;

    ss.write(reinterpret_cast<char*>(&data), sizeof(data));

    return SendData(ss.str());
}

bool MapRemote::SellUnit(Position pos, int owner)
{
    std::stringstream ss;

    RPCStructType dataType{};
    dataType = RPCStructType::RPC_BASIC_ONE_POSITION;
    ss.write(reinterpret_cast<char*>(&dataType), sizeof(dataType));

    RPCBasicOnePositionStruct data;
    data.m_RPCClassMethod = RPCClassMethodType::Map_SellUnit;
    data.m_turn = GameSession::GetInstance().GetWorldState()->GetCurrentTurn();
    data.m_requestingPlayerID = owner;
    data.m_position = pos;

    ss.write(reinterpret_cast<char*>(&data), sizeof(data));

    return SendData(ss.str());
}

std::set<Position> MapRemote::UpgradeUnit(Position pos, int owner)
{
    std::stringstream ss;

    RPCStructType dataType{};
    dataType = RPCStructType::RPC_BASIC_ONE_POSITION;
    ss.write(reinterpret_cast<char*>(&dataType), sizeof(dataType));

    RPCBasicOnePositionStruct data;
    data.m_RPCClassMethod = RPCClassMethodType::Map_UpgradeUnit;
    data.m_turn = GameSession::GetInstance().GetWorldState()->GetCurrentTurn();
    data.m_requestingPlayerID = owner;
    data.m_position = pos;

    ss.write(reinterpret_cast<char*>(&data), sizeof(data));
    SendData(ss.str());
    return std::set<Position>{};
}

std::set<Position> MapRemote::UpgradeDistrict(Position pos, int owner)
{
    std::stringstream ss;

    RPCStructType dataType{};
    dataType = RPCStructType::RPC_BASIC_ONE_POSITION;
    ss.write(reinterpret_cast<char*>(&dataType), sizeof(dataType));

    RPCBasicOnePositionStruct data;
    data.m_RPCClassMethod = RPCClassMethodType::Map_UpgradeDistrict;
    data.m_turn = GameSession::GetInstance().GetWorldState()->GetCurrentTurn();
    data.m_requestingPlayerID = owner;
    data.m_position = pos;

    ss.write(reinterpret_cast<char*>(&data), sizeof(data));

    SendData(ss.str());
    return std::set<Position>{};
}

bool MapRemote::HealUnit(Position pos, int owner)
{
    std::stringstream ss;

    RPCStructType dataType{};
    dataType = RPCStructType::RPC_BASIC_ONE_POSITION;
    ss.write(reinterpret_cast<char*>(&dataType), sizeof(dataType));

    RPCBasicOnePositionStruct data;
    data.m_RPCClassMethod = RPCClassMethodType::Map_HealUnit;
    data.m_turn = GameSession::GetInstance().GetWorldState()->GetCurrentTurn();
    data.m_requestingPlayerID = owner;
    data.m_position = pos;

    ss.write(reinterpret_cast<char*>(&data), sizeof(data));

    return SendData(ss.str());
}

bool MapRemote::RepairDistrict(Position pos, int owner)
{
    std::stringstream ss;

    RPCStructType dataType{};
    dataType = RPCStructType::RPC_BASIC_ONE_POSITION;
    ss.write(reinterpret_cast<char*>(&dataType), sizeof(dataType));

    RPCBasicOnePositionStruct data;
    data.m_RPCClassMethod = RPCClassMethodType::Map_RepairDistrict;
    data.m_turn = GameSession::GetInstance().GetWorldState()->GetCurrentTurn();
    data.m_requestingPlayerID = owner;
    data.m_position = pos;

    ss.write(reinterpret_cast<char*>(&data), sizeof(data));

    return SendData(ss.str());
}

void MapRemote::RemoveFogOfWarForPlayer(int playerID)
{
    assert(false && "Remove FOW should not be used on a remote Map");
}

MapRemote* MapRemote::Deserialize(boost::property_tree::ptree mapNode)
{
    MapRemote* map = new MapRemote();
    int row = 0;
    for each (auto rowNode in mapNode)
    {
        if (rowNode.first == "SPS")
        {
            for each(auto spawnNode in rowNode.second)
            {
                if (spawnNode.first == "SP")
                {
                    map->m_spawnPositions.emplace_back(spawnNode.second.get<int>("<xmlattr>.X"), spawnNode.second.get<int>("<xmlattr>.Y"));
                }
            }
        }
        else
        {
            int column = 0;
            for each(auto tileNode in rowNode.second)
            {
                if (tileNode.first == "T")
                {
                    Position pos{ column, row };

                    switch (tileNode.second.get<int>("<xmlattr>.TT"))
                    {
                    case 0:
                        map->m_tiles[pos.Row][pos.Column] = TileGround::Deserialize(tileNode.second, pos);
                        break;
                    case 1:
                        map->m_tiles[pos.Row][pos.Column] = TileMountain::Deserialize(tileNode.second, pos);
                        break;
                    case 2:
                        map->m_tiles[pos.Row][pos.Column] = TileWater::Deserialize(tileNode.second, pos);
                        break;

                    case -1:
                    default:
                        std::string msg = ("Error while loading the map, a tile is of type unknown.");
                        throw new std::exception(msg.c_str());
                        break;
                    }
                }
                column++;
            }
            row++;
        }
    }
    return map;
}