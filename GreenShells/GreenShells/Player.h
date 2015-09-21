#pragma once
#include <vector>
#include "Unit.h"
#include "District.h"

class Player
{
	static int playerIDCounter;

	int m_playerID;
	bool m_isReadyForNewTurn;

	bool m_isAlive;

	std::vector<Unit> m_units;
	std::vector<District> m_districts;


public:
	Player();
	~Player();

	int GetPlayerID();

	void NotifyNewTurn();

	void SetPlayerReadyForNextTurn();
	bool IsPlayerReadyForNextTurn();
};

