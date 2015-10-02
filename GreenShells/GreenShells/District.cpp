#include "District.h"
#include "GameSession.h"
#include <boost\property_tree\ptree.hpp>

District::District(int& ownerID)
	:Actor(ownerID)
{
}

District::~District()
{
}

void District::NotifyNewTurn()
{
	Player player = GameSession::GetInstance().GetWorldState()->GetPlayer(m_ownerID);
	// TODO: Update all player ressources
}

boost::property_tree::ptree District::Serialize()
{
    boost::property_tree::ptree districtXml;
    districtXml.add("District", "");
    return districtXml;
}