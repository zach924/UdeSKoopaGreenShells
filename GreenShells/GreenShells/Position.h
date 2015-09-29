#pragma once
#include <string>

class Position
{
public:
	
	int X;
	int Y;

	Position(int x = -1, int y = -1);
	~Position();
	std::string ToString() const;

	friend std::ostream& operator<<(std::ostream& os, const Position& obj)
	{
		os << obj.ToString();
		return os;
	}
};