#include "UnitMelee.h"

UnitMelee::UnitMelee(int& ownerID)
	: Unit(ownerID, Unit::MELEE_ATTACK_RANGE)
{

}
UnitMelee::~UnitMelee()
{
}
