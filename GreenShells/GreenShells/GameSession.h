#pragma once
#include <string>
#include <thread>
#include <condition_variable>

#include "WorldState.h"


class RPCManager;
class Player;
class RPCDispatcher;

class GameSession
{
	std::thread m_gameSessionThread;
	std::condition_variable m_cv;
	std::mutex m_allPlayerReadyMutex;

	bool m_allPLayerReady;

	WorldState m_worldState;

	bool m_isServer;
	std::string m_serverIP;
	int m_port;

	int m_currentPlayerID;

	//Server classes
	RPCManager* m_rpcServerManager;

	GameSession();

	GameSession(GameSession const&) = delete;
	void operator = (GameSession const&) = delete;
	void Run();
public:
	static GameSession &GetInstance()
	{
		static GameSession m_gameSession;
		return m_gameSession;
	}
	~GameSession();

	WorldState* GetWorldState();

	void SetIsServer(bool isServer);
	bool IsServer();

	void SetServerIP(std::string ip);
	std::string GetServerIP();

	void SetPort(int port);
	int GetPort();

	int GetCurrentPlayerID();
	void SetCurrentPlayerID(int player);

	bool ConnectToServer();
	void PrepareGame();

	void RunGame();
	void QuitGame();
};

