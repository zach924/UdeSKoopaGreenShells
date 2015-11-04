#pragma once
#include <vector>
#include <thread>
#include <string>
#include "SynchronizedQueue.h"
#include "RPCStructs.h"

class ClientConnection;
class RPCDispatcher;
class ServerSession;

class RPCManager
{
private:
    int m_port;
    vector<ClientConnection*> m_clients;
    SynchronizedQueue<RPCEvent>* m_events;
    std::thread* m_thread;
    RPCDispatcher* m_RPCDispatcher;

public:
    RPCManager(int port);
    void StartListening();

    void SetEventQueue(SynchronizedQueue<RPCEvent>* queue);
    SynchronizedQueue<RPCEvent>* GetEventQueue();

    void SendToClients(std::string data);
    std::vector<int> GetDisconnectedPlayers();
};