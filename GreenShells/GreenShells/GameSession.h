#pragma once
class WorldState;

class GameSession
{
	WorldState* m_worldState;
public:
	GameSession();

public:
	static GameSession &GetGameSession()
	{
		static GameSession m_gameSession;
		return m_gameSession;
	}
	~GameSession();
private:
};

