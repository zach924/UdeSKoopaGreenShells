#pragma once

#include <thread>
#include "TCPConnection.h"
#include "RPCStructs.h"
#include "SynchronizedQueue.h"

class ClientConnection
{
private:
	int m_playerID;
	bool m_isSocketClosed;
	TCPConnection m_tcpConnection;
	std::thread* m_thread;
	SynchronizedQueue<RPCEvent>* m_queue;

	void ReadSocket();

public:
	ClientConnection();
	void StartThread();

	TCPConnection& GetTCPConnection();
	int GetPlayerID();
	void SetPlayerID(int id);
	void SetIsSocketClosed(bool value=true);
	bool IsSocketClosed();
	void SetQueuePointer(SynchronizedQueue<RPCEvent>* queue);
};