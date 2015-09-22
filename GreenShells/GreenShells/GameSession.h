#pragma once
#include <string>
#include <thread>
#include "WorldState.h"


class GameSession
{
	std::thread m_gameSessionThread;
	WorldState m_worldState;

	bool m_isServer;
	std::string m_serverIP;
	int m_port;

	GameSession();

	GameSession(GameSession const&) = delete;
	void operator = (GameSession const&) = delete;
	void Run();
public:
	static GameSession &GetGameSession()
	{
		static GameSession m_gameSession;
		return m_gameSession;
	}
	~GameSession();

	void SetIsServer(bool isServer);
	bool IsServer();

	void SetServerIP(std::string ip);
	std::string GetServerIP();

	void SetPort(int port);
	int GetPort();

	void PrepareGame();

	void RunGame();
	void QuitGame();
};

