#pragma once
class WorldState;
class Map;
class Player;

class GameSession
{
	WorldState* m_worldState;
public:
	GameSession();

	//std::vector<Player*> m_players;

public:
	static GameSession &GetGameSession()
	{
		static GameSession m_gameSession;
		return m_gameSession;
	}
	~GameSession();

	void PrepareGameSession();

	void Run();

	void AddPlayer(Player * player = nullptr);

	//void AddPlayer(Player * player = nullptr);

private:
	//void GenerateTiles();

};

