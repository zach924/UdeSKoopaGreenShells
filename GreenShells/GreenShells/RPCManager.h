#pragma once
#include <vector>
#include <thread>
#include "SynchronizedQueue.h"
#include "RPCStructs.h"

class ClientConnection;

class RPCManager
{

private:
	int m_port;
	vector<ClientConnection*> m_clients;
	SynchronizedQueue<RPCEvent> m_events;
	std::thread* m_thread;
	

public:
	RPCManager(int port);
	void startListening();
};