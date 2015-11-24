#pragma once

#include <string>
#include "Position.h"
#include "Skills.h"

using namespace std;

/*
When creating a new struct to send over the network, don't forget to add the corresponding name in the enum
*/
struct PlayerInfoStruct
{
    int playerID;
    char playerName[50];

    void setPlayerName(std::string name)
    {
        strncpy_s(playerName, name.c_str(), sizeof(playerName));
        playerName[sizeof(playerName) - 1] = 0;
    }

    std::string getPlayerName()
    {
        return string(playerName);
    }
};

enum RPCStructType
{
    RPC_BASIC,
    RPC_BASIC_ONE_POSITION,
    RPC_BASIC_TWO_POSITIONS,
    RPC_BASIC_CREATION,
    RPC_BASIC_UNLOCK_SKILL,
    RPC_BASIC_DIPLOMACY_REQUEST,
    RPC_BASIC_DIPLOMACY_RESPONSE,
};

enum RPCClassMethodType
{
    //Class_Method,
    Map_Move,
    Map_Attack,
    Map_CreateUnit,
    Map_CreateDistrict,
    Map_SellUnit,
    Map_SellDistrict,
    Map_HealUnit,
    Map_RepairDistrict,
    Map_UpgradeUnit,
    Map_UpgradeDistrict,
    Player_SetReady,
    Player_UnlockSkill,
    Player_SendPeaceRequest,
    Player_SendAllianceRequest,
    Player_RespondPeace,
    Player_RespondAlliance,
    Player_DeclareWar,
};

struct RPCBasicStruct
{
    int m_turn;
    int m_requestingPlayerID;
    RPCClassMethodType m_RPCClassMethod;

    virtual bool virtualMethodForCompile()
    {
        return false;
    }
};

struct RPCBasicOnePositionStruct : public RPCBasicStruct
{
    Position m_position;
};

struct RPCBasicTwoPositionsStruct : public RPCBasicStruct
{
    Position m_firstPosition;
    Position m_secondPosition;
};

struct RPCBasicActorCreationStruct : public RPCBasicStruct
{
    Position m_positionToCreate;
    int m_actorType;
};

struct RPCBasicUnlockSkill : public RPCBasicStruct
{
    Skills m_Skill;
};

struct RPCBasicDiplomaticRequestStruct : RPCBasicStruct
{
    int m_otherPlayerId;
};

struct RPCBasicDiplomaticResponseStruct : RPCBasicDiplomaticRequestStruct
{
    bool m_response;
};

struct RPCEvent
{
    RPCStructType structType;
    RPCBasicStruct* data;
};