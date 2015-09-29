#include <iostream>

#include "RPCDispatcher.h"
#include "WorldState.h"
#include "Map.h"

void RPCDispatcher::Dispatch(RPCBasicStruct * data)
{
	switch (data->m_RPCClassMethod)
	{
		break;
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
		case RPCStructType::RPC_BASIC_TWO_POSITIONS:
			Dispatch(dynamic_cast<RPCBasicTwoPositionsStruct*>(event.data));
			break;
		}
	}
	else
	{
		std::cout << "Refused an event because it's on the previous turn." << std::endl;
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

void RPCDispatcher::Dispatch()
{
	if (!m_queue->IsEmtpy())
	{
		auto eventList = m_queue->pop();

		for (RPCEvent event : eventList)
		{
			Dispatch(event);
		}
	}
}

