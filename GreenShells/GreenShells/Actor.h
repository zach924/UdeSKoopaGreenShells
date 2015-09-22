#include "Position.h"

#pragma once
class Actor
{
	Position m_position;
public:
	Actor();
	~Actor();

	virtual void NotifyNewTurn() = 0;
};

