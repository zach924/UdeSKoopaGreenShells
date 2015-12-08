#include <iostream>
#include <sstream>
#include <assert.h>
#include <boost\property_tree\ptree.hpp>
#include <boost\property_tree\xml_parser.hpp>
#include <set>

#include "RPCDispatcher.h"
#include "WorldState.h"
#include "Map.h"
#include "Player.h"

std::vector< std::pair<ReplicationType, std::string> > RPCDispatcher::Dispatch(RPCBasicStruct * data)
{
    std::vector< std::pair<ReplicationType, std::string> > toReplicate{};
    std::stringstream ss;
    switch (data->m_RPCClassMethod)
    {
    case RPCClassMethodType::Player_SetReady:
        m_worldState->GetPlayer(data->m_requestingPlayerID)->SetPlayerReadyForNextTurn();

        boost::property_tree::write_xml(ss, m_worldState->GetPlayer(data->m_requestingPlayerID)->SerializeOnlyPlayer());
        toReplicate.push_back(std::pair<ReplicationType, std::string>{ReplicationType::PLAYER, ss.str()});
        break;
    default:
        assert(false && "You must add your code here");
    }
    return toReplicate;
}

std::vector< std::pair<ReplicationType, std::string> > RPCDispatcher::Dispatch(RPCBasicOnePositionStruct* data)
{
    std::set<Position> posToReplicate;
    std::vector< std::pair<ReplicationType, std::string> > toReplicate{};
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
        posToReplicate = m_worldState->GetMap()->UpgradeDistrict(data->m_position, data->m_requestingPlayerID);
        break;
    case RPCClassMethodType::Map_UpgradeUnit:
        posToReplicate = m_worldState->UpgradeUnit(data->m_position, data->m_requestingPlayerID);
        break;
    default:
        assert(false && "You must add your code here");
    }
    {
        std::stringstream ss;
        boost::property_tree::write_xml(ss, m_worldState->GetMap()->GetTile(data->m_position)->SerializeOnlyTile());
        toReplicate.push_back(std::pair<ReplicationType, std::string>{ReplicationType::TILE, ss.str()});
    }
    for (auto pos : posToReplicate)
    {
        std::stringstream ss;
        boost::property_tree::write_xml(ss, m_worldState->GetMap()->GetTile(pos)->SerializeOnlyTile());
        toReplicate.push_back(std::pair<ReplicationType, std::string>{ReplicationType::TILE, ss.str()});
    }
    return toReplicate;
}

std::vector< std::pair<ReplicationType, std::string> > RPCDispatcher::Dispatch(RPCBasicTwoPositionsStruct* data)
{
    std::vector< std::pair<ReplicationType, std::string> > toReplicate{};
    switch (data->m_RPCClassMethod)
    {
    default:
        assert(false && "You must add your code here");
    }
    return toReplicate;
}

std::vector< std::pair<ReplicationType, std::string> > RPCDispatcher::Dispatch(RPCBasicTwoPositionsAndCostStruct * data)
{
    std::set<Position> posToReplicate;
    std::vector< std::pair<ReplicationType, std::string> > toReplicate{};
    switch (data->m_RPCClassMethod)
    {
    case RPCClassMethodType::Map_Move:
        posToReplicate = m_worldState->GetMap()->MoveUnit(data->m_requestingPlayerID, data->m_firstPosition, data->m_secondPosition, data->m_actionCost);
        break;
    case RPCClassMethodType::Map_Attack:
        posToReplicate = m_worldState->GetMap()->Attack(data->m_requestingPlayerID, data->m_firstPosition, data->m_secondPosition, data->m_actionCost);
        break;
    default:
        assert(false && "You must add your code here");
    }
    {
        std::stringstream ss;
        boost::property_tree::write_xml(ss, m_worldState->GetMap()->GetTile(data->m_firstPosition)->SerializeOnlyTile());
        toReplicate.push_back(std::pair<ReplicationType, std::string>{ReplicationType::TILE, ss.str()});
    }
    {
        std::stringstream ss;
        boost::property_tree::write_xml(ss, m_worldState->GetMap()->GetTile(data->m_secondPosition)->SerializeOnlyTile());
        toReplicate.push_back(std::pair<ReplicationType, std::string>{ReplicationType::TILE, ss.str()});
    }

    for (auto pos : posToReplicate)
    {
        std::stringstream ss;
        boost::property_tree::write_xml(ss, m_worldState->GetMap()->GetTile(pos)->SerializeOnlyTile());
        toReplicate.push_back(std::pair<ReplicationType, std::string>{ReplicationType::TILE, ss.str()});
    }
    return toReplicate;
}

std::vector< std::pair<ReplicationType, std::string> > RPCDispatcher::Dispatch(RPCBasicActorCreationStruct * data)
{
    std::set<Position> posToReplicate;
    std::vector< std::pair<ReplicationType, std::string> > toReplicate{};
    switch (data->m_RPCClassMethod)
    {
    case RPCClassMethodType::Map_CreateDistrict:
        posToReplicate = m_worldState->GetMap()->CreateDistrict(data->m_actorType, data->m_positionToCreate, data->m_requestingPlayerID, false);
        break;
    case RPCClassMethodType::Map_CreateUnit:
        posToReplicate = m_worldState->GetMap()->CreateUnit(data->m_actorType, data->m_positionToCreate, data->m_requestingPlayerID, false);
        break;
    default:
        assert(false && "You must add your code here");
    }
    std::stringstream ss;
    boost::property_tree::write_xml(ss, m_worldState->GetMap()->GetTile(data->m_positionToCreate)->SerializeOnlyTile());
    toReplicate.push_back(std::pair<ReplicationType, std::string>{ReplicationType::TILE, ss.str()});

    for (auto pos : posToReplicate)
    {
        std::stringstream ss;
        boost::property_tree::write_xml(ss, m_worldState->GetMap()->GetTile(pos)->SerializeOnlyTile());
        toReplicate.push_back(std::pair<ReplicationType, std::string>{ReplicationType::TILE, ss.str()});
    }
    return toReplicate;
}

std::vector< std::pair<ReplicationType, std::string> > RPCDispatcher::Dispatch(RPCBasicDiplomaticRequestStruct * data)
{
    std::vector< std::pair<ReplicationType, std::string> > toReplicate{};
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
    {
        std::stringstream ss;
        boost::property_tree::write_xml(ss, m_worldState->GetPlayer(data->m_otherPlayerId)->SerializeOnlyPlayer());
        toReplicate.push_back(std::pair<ReplicationType, std::string>{ReplicationType::PLAYER, ss.str()});
    }
    {
        std::stringstream ss;
        boost::property_tree::write_xml(ss, m_worldState->GetPlayer(data->m_requestingPlayerID)->SerializeOnlyPlayer());
        toReplicate.push_back(std::pair<ReplicationType, std::string>{ReplicationType::PLAYER, ss.str()});
    }
    return toReplicate;
}

std::vector< std::pair<ReplicationType, std::string> > RPCDispatcher::Dispatch(RPCBasicDiplomaticResponseStruct * data)
{
    std::vector< std::pair<ReplicationType, std::string> > toReplicate{};
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
    {
        std::stringstream ss;
        boost::property_tree::write_xml(ss, m_worldState->GetPlayer(data->m_otherPlayerId)->SerializeOnlyPlayer());
        toReplicate.push_back(std::pair<ReplicationType, std::string>{ReplicationType::PLAYER, ss.str()});
    }
    {
        std::stringstream ss;
        boost::property_tree::write_xml(ss, m_worldState->GetPlayer(data->m_requestingPlayerID)->SerializeOnlyPlayer());
        toReplicate.push_back(std::pair<ReplicationType, std::string>{ReplicationType::PLAYER, ss.str()});
    }
    return toReplicate;
}

std::vector< std::pair<ReplicationType, std::string> > RPCDispatcher::Dispatch(RPCBasicUnlockSkill * data)
{
    std::vector< std::pair<ReplicationType, std::string> > toReplicate{};
    std::stringstream ss;
    switch (data->m_RPCClassMethod)
    {
    case RPCClassMethodType::Player_UnlockSkill:
        m_worldState->GetPlayer(data->m_requestingPlayerID)->UnlockSkill(data->m_turn, data->m_Skill);

        boost::property_tree::write_xml(ss, m_worldState->GetPlayer(data->m_requestingPlayerID)->SerializeOnlyPlayer());
        toReplicate.emplace_back(ReplicationType::PLAYER, ss.str());
        break;
    }
    return toReplicate;
}

std::vector< std::pair<ReplicationType, std::string> > RPCDispatcher::Dispatch(RPCEvent event)
{
    if (event.data->m_turn == m_worldState->GetCurrentTurn())
    {
        switch (event.structType)
        {
        case RPCStructType::RPC_BASIC:
            return Dispatch(event.data);
            break;
        case RPCStructType::RPC_BASIC_ONE_POSITION:
            return Dispatch(dynamic_cast<RPCBasicOnePositionStruct*>(event.data));
            break;
        case RPCStructType::RPC_BASIC_TWO_POSITIONS:
            return Dispatch(dynamic_cast<RPCBasicTwoPositionsStruct*>(event.data));
            break;
        case RPCStructType::RPC_BASIC_TWO_POSITIONS_AND_COST:
            return Dispatch(dynamic_cast<RPCBasicTwoPositionsAndCostStruct*>(event.data));
            break;
        case RPCStructType::RPC_BASIC_CREATION:
            return Dispatch(dynamic_cast<RPCBasicActorCreationStruct*>(event.data));
            break;
        case RPCStructType::RPC_BASIC_UNLOCK_SKILL:
            return Dispatch(dynamic_cast<RPCBasicUnlockSkill*>(event.data));
            break;
        case RPCStructType::RPC_BASIC_DIPLOMACY_REQUEST:
            return Dispatch(dynamic_cast<RPCBasicDiplomaticRequestStruct*>(event.data));
            break;
        case RPCStructType::RPC_BASIC_DIPLOMACY_RESPONSE:
            return Dispatch(dynamic_cast<RPCBasicDiplomaticResponseStruct*>(event.data));
        }
    }
    else
    {
    }
    return std::vector< std::pair<ReplicationType, std::string> > {};
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
            auto result = Dispatch(event);
            toReplicate.insert(toReplicate.end(), result.begin(), result.end());
            delete event.data;
        }
    }
    return toReplicate;
}