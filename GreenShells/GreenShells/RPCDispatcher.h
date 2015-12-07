#pragma once
#include <vector>
#include <string>
#include "SynchronizedQueue.h"
#include "RPCStructs.h"

class WorldState;

class RPCDispatcher
{
    SynchronizedQueue<RPCEvent>* m_queue;
    WorldState* m_worldState;

    std::vector< std::pair<ReplicationType, std::string> > Dispatch(RPCBasicStruct* data);
    std::vector< std::pair<ReplicationType, std::string> > Dispatch(RPCBasicTwoPositionsStruct* data);
    std::vector< std::pair<ReplicationType, std::string> > Dispatch(RPCBasicOnePositionStruct* data);
    std::vector< std::pair<ReplicationType, std::string> > Dispatch(RPCBasicTwoPositionsAndCostStruct* data);
    std::vector< std::pair<ReplicationType, std::string> > Dispatch(RPCBasicActorCreationStruct* data);
    std::vector< std::pair<ReplicationType, std::string> > Dispatch(RPCBasicUnlockSkill* data);
    std::vector< std::pair<ReplicationType, std::string> > Dispatch(RPCBasicDiplomaticRequestStruct* data);
    std::vector< std::pair<ReplicationType, std::string> > Dispatch(RPCBasicDiplomaticResponseStruct* data);
    std::vector< std::pair<ReplicationType, std::string> > Dispatch(RPCEvent);

public:
    RPCDispatcher();
    ~RPCDispatcher();

    void SetWorldState(WorldState* worldState);
    WorldState* GetWorldState();

    void SetEventQueue(SynchronizedQueue<RPCEvent>* queue);
    SynchronizedQueue<RPCEvent>* GetEventQueue();

    std::vector< std::pair<ReplicationType, std::string> > Dispatch();
};