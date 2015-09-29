#pragma once
#include <string>
class Position
{
public:
	
	int X;
	int Y;

	Position(int x = -1, int y = -1);
	~Position();
	std::string ToString();
};

