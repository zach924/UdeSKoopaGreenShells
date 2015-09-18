#pragma once
class WorldState;

class GameSession
{
	WorldState* m_worldState;

	bool m_isServer;

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
};

