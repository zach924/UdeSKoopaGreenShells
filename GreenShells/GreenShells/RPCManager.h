#pragma once
#include <vector>
#include <thread>
#include "SynchronizedQueue.h"
#include "RPCStructs.h"

class ClientConnection;
class RPCDispatcher;
class WorldState;

class RPCManager
{
private:
	int m_port;
	vector<ClientConnection*> m_clients;
	SynchronizedQueue<RPCEvent>* m_events;
	std::thread* m_thread;
	WorldState* m_worldState;



	RPCDispatcher* m_RPCDispatcher;

public:
	RPCManager(int port);
	void StartListening();

	void SetEventQueue(SynchronizedQueue<RPCEvent>* queue);
	SynchronizedQueue<RPCEvent>* GetEventQueue();

	void SetWorldState(WorldState* worldState);
	WorldState* GetWorldState();
};