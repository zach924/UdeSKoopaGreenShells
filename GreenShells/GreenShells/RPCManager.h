#pragma once
#include <vector>
#include <thread>
#include "SynchronizedQueue.h"
#include "RPCStructs.h"


class ClientConnection;
class RPCDispatcher;

class RPCManager
{

private:
	int m_port;
	vector<ClientConnection*> m_clients;
	SynchronizedQueue<RPCEvent> m_events;
	std::thread* m_thread;

	RPCDispatcher* m_RPCDispatcher;

public:
	RPCManager(int port);
	void StartListening();

	void SetRPCDispatcher(RPCDispatcher* dispatcher);
	RPCDispatcher* GetRPCDispatcher();

	void DispatchEvents();
};