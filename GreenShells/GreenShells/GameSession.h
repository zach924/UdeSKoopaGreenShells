#pragma once
#include <string>

class WorldState;

class GameSession
{
	WorldState* m_worldState;

	bool m_isServer;
	std::string m_serverIP;
	int m_port;

	GameSession();
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
	int getPort();
};

