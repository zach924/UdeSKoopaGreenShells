#pragma once
#include <atomic>
#include "RPCManager.h"
#include "RPCDispatcher.h"
#include "SynchronizedQueue.h"
#include "WorldState.h"

class ServerSession
{
    RPCDispatcher* m_dispatcher;
    RPCManager* m_rpcServerManager;
    SynchronizedQueue<RPCEvent> m_events;

    std::thread* m_serverSessionThread;

    atomic<bool> m_isStopped;

    ServerSession();
    ServerSession(ServerSession const&) = delete;
    void operator = (ServerSession const&) = delete;

    void run();
    WorldState m_worldState;
public:
    static ServerSession &GetInstance()
    {
        static ServerSession m_serverSession;
        return m_serverSession;
    }
    ~ServerSession();

    void StartServer(int port);
    void StopServer();
    void Replicate();
    WorldState* GetWorldState();

    int AddPlayer(std::string playerName);

};
