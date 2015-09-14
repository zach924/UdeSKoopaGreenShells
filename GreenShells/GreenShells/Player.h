#pragma once
#include <vector>

class Unit;
class District;

class Player
{
	std::vector<Unit> m_units;
	std::vector<District> m_districts;

public:
	Player();
	~Player();
};

