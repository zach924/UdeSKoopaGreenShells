#pragma once
#include <string>
#include <thread>
#include <condition_variable>

#include "WorldState.h"

class GameSession
{
    WorldState m_worldState;

    std::string m_serverIP;
    int m_port;
    int m_currentPlayerID;

    std::thread* m_replicationThread;

    GameSession();
    GameSession(GameSession const&) = delete;
    void operator = (GameSession const&) = delete;
    ~GameSession();
public:
    static GameSession &GetInstance()
    {
        static GameSession m_gameSession;
        return m_gameSession;
    }

    WorldState* GetWorldState();

    void SetServerIP(std::string ip);
    std::string GetServerIP();

    void SetPort(int port);
    int GetPort();

    int GetCurrentPlayerID();
    void SetCurrentPlayerID(int player);

    bool ConnectToServer(char* playerName);

    void Save(std::string fileName);
    void Load(std::string fileName);

    void FetchReplication();
    void FetchReplicationThread();
};
