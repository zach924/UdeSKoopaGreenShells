#include "Unit.h"
#include "GameSession.h"

#include <boost\property_tree\ptree.hpp>

Unit::Unit(const int& ownerID, const Position& pos)
	:Actor(ownerID,pos)
{
}

Unit::~Unit()
{
}

boost::property_tree::ptree Unit::Serialize()
{
    boost::property_tree::ptree unitXml;
    unitXml.add("Unit", "");
    return unitXml;
}

void Unit::NotifyNewTurn()
{
	Player player = GameSession::GetInstance().GetWorldState()->GetPlayer(m_ownerID);
	// TODO: Update all player ressources
}