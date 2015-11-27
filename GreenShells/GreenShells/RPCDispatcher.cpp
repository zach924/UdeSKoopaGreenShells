#include <iostream>
#include <assert.h>

#include "RPCDispatcher.h"
#include "WorldState.h"
#include "Map.h"
#include "Player.h"

void RPCDispatcher::Dispatch(RPCBasicStruct * data)
{
    switch (data->m_RPCClassMethod)
    {
    case RPCClassMethodType::Player_SetReady:
        m_worldState->GetPlayer(data->m_requestingPlayerID)->SetPlayerReadyForNextTurn();
        break;
    default:
        assert(false && "You must add your code here");
    }
}

void RPCDispatcher::Dispatch(RPCBasicOnePositionStruct * data)
{
    switch (data->m_RPCClassMethod)
    {
    case RPCClassMethodType::Map_SellDistrict:
        m_worldState->GetMap()->SellDistrict(data->m_position, data->m_requestingPlayerID);
        break;
    case RPCClassMethodType::Map_SellUnit:
        m_worldState->GetMap()->SellUnit(data->m_position, data->m_requestingPlayerID);
        break;
    case RPCClassMethodType::Map_HealUnit:
        m_worldState->GetMap()->HealUnit(data->m_position, data->m_requestingPlayerID);
        break;
    case RPCClassMethodType::Map_RepairDistrict:
        m_worldState->GetMap()->RepairDistrict(data->m_position, data->m_requestingPlayerID);
        break;
    case RPCClassMethodType::Map_UpgradeDistrict:
        m_worldState->GetMap()->UpgradeDistrict(data->m_position, data->m_requestingPlayerID);
        break;
    case RPCClassMethodType::Map_UpgradeUnit:
        m_worldState->UpgradeUnit(data->m_position, data->m_requestingPlayerID);
        break;
    default:
        assert(false && "You must add your code here");
    }

}

void RPCDispatcher::Dispatch(RPCBasicTwoPositionsStruct * data)
{
    switch (data->m_RPCClassMethod)
    {
    case RPCClassMethodType::Map_Move:
        //go move the unit
        m_worldState->GetMap()->MoveUnit(data->m_requestingPlayerID, data->m_firstPosition, data->m_secondPosition);
        break;
    case RPCClassMethodType::Map_Attack:
        // Do the attack
        m_worldState->GetMap()->Attack(data->m_requestingPlayerID, data->m_firstPosition, data->m_secondPosition);
        break;
    default:
        assert(false && "You must add your code here");
    }
}

void RPCDispatcher::Dispatch(RPCBasicActorCreationStruct * data)
{
    switch (data->m_RPCClassMethod)
    {
    case RPCClassMethodType::Map_CreateDistrict:
        m_worldState->GetMap()->CreateDistrict(data->m_actorType, data->m_positionToCreate, data->m_requestingPlayerID);
        break;
    case RPCClassMethodType::Map_CreateUnit:
        m_worldState->GetMap()->CreateUnit(data->m_actorType, data->m_positionToCreate, data->m_requestingPlayerID);
        break;
    default:
        assert(false && "You must add your code here");
    }
}

void RPCDispatcher::Dispatch(RPCBasicDiplomaticRequestStruct * data)
{
    switch (data->m_RPCClassMethod)
    {
    case RPCClassMethodType::Player_SendPeaceRequest:
        m_worldState->GetPlayer(data->m_requestingPlayerID)->SendPeaceProposition(data->m_otherPlayerId, data->m_turn);
        m_worldState->GetPlayer(data->m_otherPlayerId)->ReceivePeaceProposition(data->m_requestingPlayerID, data->m_turn);
        break;
    case RPCClassMethodType::Player_SendAllianceRequest:
        m_worldState->GetPlayer(data->m_requestingPlayerID)->SendAllianceProposition(data->m_otherPlayerId, data->m_turn);
        m_worldState->GetPlayer(data->m_otherPlayerId)->ReceiveAllianceProposition(data->m_requestingPlayerID, data->m_turn);
        break;
    case RPCClassMethodType::Player_DeclareWar:
        m_worldState->GetPlayer(data->m_requestingPlayerID)->GoToWar(data->m_otherPlayerId, data->m_turn);
        m_worldState->GetPlayer(data->m_otherPlayerId)->GoToWar(data->m_requestingPlayerID, data->m_turn);
        break;
    default:
        assert(false && "You must add your code here");
    }
}

void RPCDispatcher::Dispatch(RPCBasicDiplomaticResponseStruct * data)
{
    switch (data->m_RPCClassMethod)
    {

    case RPCClassMethodType::Player_RespondPeace:
        if (data->m_response)
        {
            m_worldState->GetPlayer(data->m_requestingPlayerID)->GoToPeace(data->m_otherPlayerId, data->m_turn);
            m_worldState->GetPlayer(data->m_otherPlayerId)->GoToPeace(data->m_requestingPlayerID, data->m_turn);
        }
        else
        {
            m_worldState->GetPlayer(data->m_requestingPlayerID)->GoToWar(data->m_otherPlayerId, data->m_turn);
            m_worldState->GetPlayer(data->m_otherPlayerId)->GoToWar(data->m_requestingPlayerID, data->m_turn);
        }
        break;
    case RPCClassMethodType::Player_RespondAlliance:
        if (data->m_response)
        {
            m_worldState->GetPlayer(data->m_requestingPlayerID)->GoToAlliance(data->m_otherPlayerId, data->m_turn);
            m_worldState->GetPlayer(data->m_otherPlayerId)->GoToAlliance(data->m_requestingPlayerID, data->m_turn);
        }
        else
        {
            m_worldState->GetPlayer(data->m_requestingPlayerID)->GoToPeace(data->m_otherPlayerId, data->m_turn);
            m_worldState->GetPlayer(data->m_otherPlayerId)->GoToPeace(data->m_requestingPlayerID, data->m_turn);
        }
        break;
    default:
        assert(false && "You must add your code here");
    }
}

void RPCDispatcher::Dispatch(RPCBasicUnlockSkill * data)
{
    switch (data->m_RPCClassMethod)
    {
    case RPCClassMethodType::Player_UnlockSkill:
        m_worldState->GetPlayer(data->m_requestingPlayerID)->UnlockSkill(data->m_turn, data->m_Skill);
        break;
    }
}

void RPCDispatcher::Dispatch(RPCEvent event)
{
    if (event.data->m_turn == m_worldState->GetCurrentTurn())
    {
        switch (event.structType)
        {
        case RPCStructType::RPC_BASIC:
            Dispatch(event.data);
            break;
        case RPCStructType::RPC_BASIC_ONE_POSITION:
            Dispatch(dynamic_cast<RPCBasicOnePositionStruct*>(event.data));
            break;
        case RPCStructType::RPC_BASIC_TWO_POSITIONS:
            Dispatch(dynamic_cast<RPCBasicTwoPositionsStruct*>(event.data));
            break;
        case RPCStructType::RPC_BASIC_CREATION:
            Dispatch(dynamic_cast<RPCBasicActorCreationStruct*>(event.data));
            break;
        case RPCStructType::RPC_BASIC_UNLOCK_SKILL:
            Dispatch(dynamic_cast<RPCBasicUnlockSkill*>(event.data));
            break;
        case RPCStructType::RPC_BASIC_DIPLOMACY_REQUEST:
            Dispatch(dynamic_cast<RPCBasicDiplomaticRequestStruct*>(event.data));
            break;
        case RPCStructType::RPC_BASIC_DIPLOMACY_RESPONSE:
            Dispatch(dynamic_cast<RPCBasicDiplomaticResponseStruct*>(event.data));
        }
    }
    else
    {
        std::cout << "Refused an event because it's on the previous turn." << std::endl << "Current turn : " << m_worldState->GetCurrentTurn() << " Event turn : " << event.data->m_turn << std::endl;
    }
}

RPCDispatcher::RPCDispatcher()
{
}

RPCDispatcher::~RPCDispatcher()
{
}

void RPCDispatcher::SetWorldState(WorldState* worldState)
{
    m_worldState = worldState;
}

WorldState* RPCDispatcher::GetWorldState()
{
    return m_worldState;
}

void RPCDispatcher::SetEventQueue(SynchronizedQueue<RPCEvent>* queue)
{
    m_queue = queue;
}

SynchronizedQueue<RPCEvent>* RPCDispatcher::GetEventQueue()
{
    return m_queue;
}

bool RPCDispatcher::Dispatch()
{
    if (!m_queue->IsEmtpy())
    {
        auto eventList = m_queue->pop();

        for (RPCEvent event : eventList)
        {
            Dispatch(event);
            delete event.data;
        }

        return true;
    }
    return false;
}