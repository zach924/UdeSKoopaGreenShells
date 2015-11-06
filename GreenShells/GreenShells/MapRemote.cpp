#include <sstream>
#include "MapRemote.h"
#include "RPCStructs.h"
#include "GameSession.h"

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

bool MapRemote::MoveUnit(int ownerID, Position unitLocation, Position newLocation)
{
    std::stringstream ss;

    RPCStructType dataType{};
    dataType = RPCStructType::RPC_BASIC_TWO_POSITIONS;
    ss.write(reinterpret_cast<char*>(&dataType), sizeof(dataType));

    RPCBasicTwoPositionsStruct data;
    data.m_RPCClassMethod = RPCClassMethodType::Map_Move;
    data.m_turn = GameSession::GetInstance().GetWorldState()->GetCurrentTurn();
    data.m_requestingPlayerID = ownerID;
    data.m_firstPosition = unitLocation;
    data.m_secondPosition = newLocation;

    ss.write(reinterpret_cast<char*>(&data), sizeof(data));
    return SendData(ss.str());
}

bool MapRemote::Attack(int ownerID, Position attackerPosition, Position targetPosition)
{
    std::stringstream ss;

    RPCStructType dataType{};
    dataType = RPCStructType::RPC_BASIC_TWO_POSITIONS;
    ss.write(reinterpret_cast<char*>(&dataType), sizeof(dataType));

    RPCBasicTwoPositionsStruct data;
    data.m_RPCClassMethod = RPCClassMethodType::Map_Attack;
    data.m_turn = GameSession::GetInstance().GetWorldState()->GetCurrentTurn();
    data.m_requestingPlayerID = ownerID;
    data.m_firstPosition = attackerPosition;
    data.m_secondPosition = targetPosition;

    ss.write(reinterpret_cast<char*>(&data), sizeof(data));

    return SendData(ss.str());
}

bool MapRemote::CreateUnit(int unitType, Position pos, int owner)
{
    std::stringstream ss;

    RPCStructType dataType{};
    dataType = RPCStructType::RPC_BASIC_CREATION;
    ss.write(reinterpret_cast<char*>(&dataType), sizeof(dataType));

    RPCBasicCreationStruct data;
    data.m_RPCClassMethod = RPCClassMethodType::Map_CreateUnit;
    data.m_turn = GameSession::GetInstance().GetWorldState()->GetCurrentTurn();
    data.m_requestingPlayerID = owner;
    data.m_positionToCreate = pos;
    data.m_id = unitType;

    ss.write(reinterpret_cast<char*>(&data), sizeof(data));

    return SendData(ss.str());
}

bool MapRemote::CreateDistrict(int districtType, Position pos, int owner)
{
    std::stringstream ss;

    RPCStructType dataType{};
    dataType = RPCStructType::RPC_BASIC_CREATION;
    ss.write(reinterpret_cast<char*>(&dataType), sizeof(dataType));

    RPCBasicCreationStruct data;
    data.m_RPCClassMethod = RPCClassMethodType::Map_CreateDistrict;
    data.m_turn = GameSession::GetInstance().GetWorldState()->GetCurrentTurn();
    data.m_requestingPlayerID = owner;
    data.m_positionToCreate = pos;
    data.m_id = districtType;

    ss.write(reinterpret_cast<char*>(&data), sizeof(data));

    return SendData(ss.str());
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