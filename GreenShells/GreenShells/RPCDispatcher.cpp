#include <iostream>
#include <sstream>
#include <assert.h>
#include <boost\property_tree\ptree.hpp>
#include <boost\property_tree\xml_parser.hpp>

#include "RPCDispatcher.h"
#include "WorldState.h"
#include "Map.h"
#include "Player.h"

std::pair<ReplicationType, std::string> RPCDispatcher::Dispatch(RPCBasicStruct * data)
{
        std::stringstream ss;
    switch (data->m_RPCClassMethod)
    {
    case RPCClassMethodType::Player_SetReady:
        m_worldState->GetPlayer(data->m_requestingPlayerID)->SetPlayerReadyForNextTurn();

        boost::property_tree::write_xml(ss, m_worldState->GetPlayer(data->m_requestingPlayerID)->Serialize());
        return std::pair<ReplicationType, std::string>{ReplicationType::PLAYER, ss.str() };
        break;
    default:
        assert(false && "You must add your code here");
    }
}

std::pair<ReplicationType, std::string> RPCDispatcher::Dispatch(RPCBasicTwoPositionsStruct * data)
{
    switch (data->m_RPCClassMethod)
    {
    default:
        assert(false && "You must add your code here");
    }
}

std::pair<ReplicationType, std::string> RPCDispatcher::Dispatch(RPCBasicTwoPositionsAndCostStruct * data)
{
    switch (data->m_RPCClassMethod)
    {
    case RPCClassMethodType::Map_Move:
        //go move the unit
        m_worldState->GetMap()->MoveUnit(data->m_requestingPlayerID, data->m_firstPosition, data->m_secondPosition, data->m_actionCost);
        break;
    case RPCClassMethodType::Map_Attack:
        // Do the attack
        m_worldState->GetMap()->Attack(data->m_requestingPlayerID, data->m_firstPosition, data->m_secondPosition, data->m_actionCost);
        break;
    default:
        assert(false && "You must add your code here");
    }
}

std::pair<ReplicationType, std::string> RPCDispatcher::Dispatch(RPCBasicActorCreationStruct * data)
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

std::pair<ReplicationType, std::string> RPCDispatcher::Dispatch(RPCBasicDiplomaticRequestStruct * data)
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

std::pair<ReplicationType, std::string> RPCDispatcher::Dispatch(RPCBasicDiplomaticResponseStruct * data)
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

std::pair<ReplicationType, std::string> RPCDispatcher::Dispatch(RPCBasicUnlockSkill * data)
{
    switch (data->m_RPCClassMethod)
    {
    case RPCClassMethodType::Player_UnlockSkill:
        m_worldState->GetPlayer(data->m_requestingPlayerID)->UnlockSkill(data->m_turn, data->m_Skill);
        break;
    }
}

std::pair<ReplicationType, std::string> RPCDispatcher::Dispatch(RPCEvent event)
{
    if (event.data->m_turn == m_worldState->GetCurrentTurn())
    {
        switch (event.structType)
        {
        case RPCStructType::RPC_BASIC:
            Dispatch(event.data);
            break;
        case RPCStructType::RPC_BASIC_TWO_POSITIONS:
            Dispatch(dynamic_cast<RPCBasicTwoPositionsStruct*>(event.data));
            break;
        case RPCStructType::RPC_BASIC_TWO_POSITIONS_AND_COST:
            Dispatch(dynamic_cast<RPCBasicTwoPositionsAndCostStruct*>(event.data));
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

std::vector< std::pair<ReplicationType, std::string> > RPCDispatcher::Dispatch()
{
    std::vector< std::pair<ReplicationType, std::string> > toReplicate;
    if (!m_queue->IsEmtpy())
    {
        auto eventList = m_queue->pop();

        for (RPCEvent event : eventList)
        {
            toReplicate.push_back(Dispatch(event));
            delete event.data;
        }
    }
    return toReplicate;
}