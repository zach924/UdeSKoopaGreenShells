#pragma once
#include <string>
class Position
{
public:
	
	int X;
	int Y;

	Position(int x, int y);
	~Position();
	std::string ToString();
};

