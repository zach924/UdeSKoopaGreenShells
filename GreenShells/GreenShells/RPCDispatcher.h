#pragma once

#include "SynchronizedQueue.h"
#include "RPCStructs.h"

class WorldState;

class RPCDispatcher
{
    SynchronizedQueue<RPCEvent>* m_queue;
    WorldState* m_worldState;

    void Dispatch(RPCBasicStruct* data);
    void Dispatch(RPCBasicOnePositionStruct* data);
    void Dispatch(RPCBasicTwoPositionsStruct* data);
    void Dispatch(RPCBasicTwoPositionsAndCostStruct* data);
    void Dispatch(RPCBasicActorCreationStruct* data);
    void Dispatch(RPCBasicUnlockSkill* data);
    void Dispatch(RPCBasicDiplomaticRequestStruct* data);
    void Dispatch(RPCBasicDiplomaticResponseStruct* data);
    void Dispatch(RPCEvent event);

public:
    RPCDispatcher();
    ~RPCDispatcher();

    void SetWorldState(WorldState* worldState);
    WorldState* GetWorldState();

    void SetEventQueue(SynchronizedQueue<RPCEvent>* queue);
    SynchronizedQueue<RPCEvent>* GetEventQueue();

    bool Dispatch();
};