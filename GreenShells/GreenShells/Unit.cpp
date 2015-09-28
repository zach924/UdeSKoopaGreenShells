#include "Unit.h"


Unit::Unit(Player& owner)
	:Actor(owner)
{
}

Unit::~Unit()
{
}

void Unit::NotifyNewTurn()
{
}
