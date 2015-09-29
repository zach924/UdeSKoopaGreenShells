#include "Position.h"

#pragma once
class Actor
{
	Position m_position;
public:
	Actor(Position position = Position(-1,-1));
	~Actor();
};

