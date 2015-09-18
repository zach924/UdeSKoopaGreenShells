#pragma once
#include <vector>

class Unit;
class District;

class Player
{
	bool m_isReadyForNewTurn;

	std::vector<Unit> m_units;
	std::vector<District> m_districts;

	//bool m_isAlive;

public:
	Player();
	~Player();

	void NotifyNewTurn();

	void SetPlayerReadyForNextTurn();
	bool IsPlayerReadyForNextTurn();
};

