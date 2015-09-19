#include <string>
#pragma once
class Position
{
public:
	
	int X;
	int Y;

	Position(int x, int y);
	~Position();
	std::string ToString();
};

