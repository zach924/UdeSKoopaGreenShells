#include "PlayerRemote.h"
#include "RPCStructs.h"
#include "GameSession.h"
#include <sstream>
#include <iostream>
#include <boost\property_tree\ptree.hpp>

void PlayerRemote::RemoveRelation(int otherPlayerId)
{
    assert(false && "Don't use this with player remote");
}

PlayerRemote::PlayerRemote()
    :Player()
{
}

PlayerRemote::~PlayerRemote()
{
}


Player* PlayerRemote::Clone()
{
    PlayerRemote* player = new PlayerRemote{};

    player->m_playerName = m_playerName;
    player->m_playerID = m_playerID;
    player->m_isReadyForNewTurn = m_isReadyForNewTurn;
    player->m_isAlive = m_isAlive;
    player->m_isDisconnected = m_isDisconnected;
    player->m_cityCenterLocations = m_cityCenterLocations;
    player->m_unitCount = m_unitCount;
    player->m_food = m_food;
    player->m_science = m_science;
    player->m_weapon = m_weapon;
    player->m_foodMultiplier = m_foodMultiplier;
    player->m_scienceMultiplier = m_scienceMultiplier;
    player->m_weaponMultiplier = m_weaponMultiplier;
    player->m_utilitySkillTree = m_utilitySkillTree;
    player->m_armySkillTree = m_armySkillTree;
    player->m_empireSkillTree = m_empireSkillTree;
    player->m_diplomaticRelations.insert(m_diplomaticRelations.begin(), m_diplomaticRelations.end());

    return player;
}

void PlayerRemote::SetPlayerName(std::string name)
{
    assert(false && "Don't use this with player remote");
}

void PlayerRemote::SetPlayerID(int ID)
{
    assert(false && "Don't use this with player remote");
}

void PlayerRemote::NotifyNewTurn(int turn, Map* map)
{
    assert(false && "Don't use this with player remote");
}

void PlayerRemote::SetPlayerReadyForNextTurn(bool isReady)
{
    std::stringstream ss;

    RPCStructType dataType{};
    dataType = RPCStructType::RPC_BASIC;
    ss.write(reinterpret_cast<char*>(&dataType), sizeof(dataType));

    RPCBasicStruct data;
    data.m_RPCClassMethod = RPCClassMethodType::Player_SetReady;
    data.m_turn = GameSession::GetInstance().GetWorldState()->GetCurrentTurn();
    data.m_requestingPlayerID = m_playerID;

    ss.write(reinterpret_cast<char*>(&data), sizeof(data));
    SendData(ss.str());
}

void PlayerRemote::SetIsAlive(bool value)
{
    assert(false && "Don't use this with player remote");
}

void PlayerRemote::AddFood(unsigned int qty)
{
    assert(false && "Don't use this with player remote");
}

void PlayerRemote::AddScience(unsigned int qty)
{
    assert(false && "Don't use this with player remote");
}

void PlayerRemote::AddWeapon(unsigned int qty)
{
    assert(false && "Don't use this with player remote");
}

bool PlayerRemote::ConsumeFood(unsigned int qty)
{
    assert(false && "Don't use this with player remote");
    return false;
}

bool PlayerRemote::ConsumeScience(unsigned int qty)
{
    assert(false && "Don't use this with player remote");
    return false;
}

bool PlayerRemote::ConsumeWeapon(unsigned int qty)
{
    assert(false && "Don't use this with player remote");
    return false;
}

void PlayerRemote::AddFoodMultiplier(double multiplier)
{
    assert(false && "Don't use this with player remote");
}

void PlayerRemote::AddScienceMultiplier(double multiplier)
{
    assert(false && "Don't use this with player remote");
}

void PlayerRemote::AddWeaponMultiplier(double multiplier)
{
    assert(false && "Don't use this with player remote");
}

void PlayerRemote::RemoveFoodMultiplier(double multiplier)
{
    assert(false && "Don't use this with player remote");
}

void PlayerRemote::RemoveScienceMultiplier(double multiplier)
{
    assert(false && "Don't use this with player remote");
}

void PlayerRemote::RemoveWeaponMultiplier(double multiplier)
{
    assert(false && "Don't use this with player remote");
}

void PlayerRemote::AddCityCenter(Position pos, int turn)
{
    assert(false && "Don't use this with player remote");
}

void PlayerRemote::RemoveCityCenter(Position pos)
{
    assert(false && "Don't use this with player remote");
}

void PlayerRemote::SetIsDisconnected(bool value)
{
    assert(false && "Don't use this with player remote");
}

void PlayerRemote::AddNewRelation(int otherPlayerId, int currentTurn, RelationStatus status, int mustAnswerPlayerId)
{
    assert(false && "Don't use this with player remote");
}

void PlayerRemote::SendPeaceProposition(int otherPlayerId, int currentTurn)
{
    std::stringstream ss;

    RPCStructType dataType{};
    dataType = RPCStructType::RPC_BASIC_DIPLOMACY_REQUEST;
    ss.write(reinterpret_cast<char*>(&dataType), sizeof(dataType));

    RPCBasicDiplomaticRequestStruct data;
    data.m_RPCClassMethod = RPCClassMethodType::Player_SendPeaceRequest;
    data.m_turn = currentTurn;
    data.m_requestingPlayerID = m_playerID;
    data.m_otherPlayerId = otherPlayerId;

    ss.write(reinterpret_cast<char*>(&data), sizeof(data));
    SendData(ss.str());
}

void PlayerRemote::ReceivePeaceProposition(int otherPlayerId, int currentTurn)
{
    assert(false && "Don't use this with player remote");
}

void PlayerRemote::RespondPeaceProposition(int otherPlayerId, int currentTurn, bool answer)
{
    std::stringstream ss;

    RPCStructType dataType{};
    dataType = RPCStructType::RPC_BASIC_DIPLOMACY_RESPONSE;
    ss.write(reinterpret_cast<char*>(&dataType), sizeof(dataType));

    RPCBasicDiplomaticResponseStruct data;
    data.m_RPCClassMethod = RPCClassMethodType::Player_RespondPeace;
    data.m_turn = currentTurn;
    data.m_requestingPlayerID = m_playerID;
    data.m_otherPlayerId = otherPlayerId;
    data.m_response = answer;

    ss.write(reinterpret_cast<char*>(&data), sizeof(data));
    SendData(ss.str());
}

void PlayerRemote::GoToPeace(int otherPlayerId, int currentTurn)
{
    assert(false && "You can't do that with a remote player");
}

void PlayerRemote::ReceiveAllianceProposition(int otherPlayerId, int currentTurn)
{
    assert(false && "Don't use this with player remote");
}

void PlayerRemote::SendAllianceProposition(int otherPlayerId, int currentTurn)
{
    std::stringstream ss;

    RPCStructType dataType{};
    dataType = RPCStructType::RPC_BASIC_DIPLOMACY_REQUEST;
    ss.write(reinterpret_cast<char*>(&dataType), sizeof(dataType));

    RPCBasicDiplomaticRequestStruct data;
    data.m_RPCClassMethod = RPCClassMethodType::Player_SendAllianceRequest;
    data.m_turn = currentTurn;
    data.m_requestingPlayerID = m_playerID;
    data.m_otherPlayerId = otherPlayerId;

    ss.write(reinterpret_cast<char*>(&data), sizeof(data));

    SendData(ss.str());
}

void PlayerRemote::RespondAllianceProposition(int otherPlayerId, int currentTurn, bool answer)
{
    std::stringstream ss;

    RPCStructType dataType{};
    dataType = RPCStructType::RPC_BASIC_DIPLOMACY_RESPONSE;
    ss.write(reinterpret_cast<char*>(&dataType), sizeof(dataType));

    RPCBasicDiplomaticResponseStruct data;
    data.m_RPCClassMethod = RPCClassMethodType::Player_RespondAlliance;
    data.m_turn = currentTurn;
    data.m_requestingPlayerID = m_playerID;
    data.m_otherPlayerId = otherPlayerId;
    data.m_response = answer;

    ss.write(reinterpret_cast<char*>(&data), sizeof(data));
    SendData(ss.str());
}

void PlayerRemote::GoToAlliance(int otherPlayerId, int currentTurn)
{
    assert(false && "You can't do that with a remote player");
}

void PlayerRemote::GoToWar(int otherPlayerId, int currentTurn)
{
    std::stringstream ss;

    RPCStructType dataType{};
    dataType = RPCStructType::RPC_BASIC_DIPLOMACY_REQUEST;
    ss.write(reinterpret_cast<char*>(&dataType), sizeof(dataType));

    RPCBasicDiplomaticRequestStruct data;
    data.m_RPCClassMethod = RPCClassMethodType::Player_DeclareWar;
    data.m_turn = currentTurn;
    data.m_requestingPlayerID = m_playerID;
    data.m_otherPlayerId = otherPlayerId;

    ss.write(reinterpret_cast<char*>(&data), sizeof(data));
    SendData(ss.str());
}

PlayerRemote* PlayerRemote::Deserialize(boost::property_tree::ptree playerNode)
{
    PlayerRemote* player = new PlayerRemote();

    player->m_playerID = playerNode.get<int>("<xmlattr>.PId");
    player->m_playerName = playerNode.get<std::string>("<xmlattr>.PName");
    player->m_unitCount = playerNode.get<int>("<xmlattr>.UC");
    player->m_food = playerNode.get<int>("<xmlattr>.F");
    player->m_science = playerNode.get<int>("<xmlattr>.S");
    player->m_weapon = playerNode.get<int>("<xmlattr>.W");
    player->m_foodMultiplier = playerNode.get<double>("<xmlattr>.FM");
    player->m_scienceMultiplier = playerNode.get<double>("<xmlattr>.SM");
    player->m_weaponMultiplier = playerNode.get<double>("<xmlattr>.WM");
    player->m_isAlive = playerNode.get<bool>("<xmlattr>.IA");
    player->m_isReadyForNewTurn = playerNode.get<bool>("<xmlattr>.IR");
    player->m_isDisconnected = playerNode.get<bool>("<xmlattr>.ID");
    player->m_utilitySkillTree = UtilitySkillTree(playerNode.get<std::string>("<xmlattr>.UST"));
    player->m_empireSkillTree = EmpireSkillTree(playerNode.get<std::string>("<xmlattr>.EST"));
    player->m_armySkillTree = ArmySkillTree(playerNode.get<std::string>("<xmlattr>.AST"));
    for (auto cityCenterNode : playerNode.get_child("CCL"))
    {
        int column = cityCenterNode.second.get<int>("<xmlattr>.Co");
        int row = cityCenterNode.second.get<int>("<xmlattr>.Ro");
        int turnFounded = cityCenterNode.second.get<int>("<xmlattr>.TF");
        player->m_cityCenterLocations[Position{ column , row }] = turnFounded;
    }

    auto diplomaticRelationsNode = playerNode.get_child("DR");
    for (auto relationNode : diplomaticRelationsNode)
    {
        if (relationNode.first == "R")
        {
            int SP = relationNode.second.get<int>("<xmlattr>.SP");
            RelationStatus RS = static_cast<RelationStatus>(relationNode.second.get<int>("<xmlattr>.RS"));
            int MA = relationNode.second.get<int>("<xmlattr>.MA");
            int PT = relationNode.second.get<int>("<xmlattr>.PT");
            player->m_diplomaticRelations.insert(std::map<int, DiplomaticRelation>::value_type(SP, DiplomaticRelation(PT, RS, MA)));
        }
        else
        {
            assert(false && "You added a new node in player serialize. You need to Deserialize it");
        }
    }

    return player;
}