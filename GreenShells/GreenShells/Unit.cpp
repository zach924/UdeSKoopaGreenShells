#include "Unit.h"
#include "Texture.h"

#include "Swordsman.h"



Texture Swordsman::tBase::m_Texture = {};


//#include "GameSession.h"
//
//#include <boost\property_tree\ptree.hpp>
//
//Unit::Unit(int ownerID, int attackRange, int attackDamage)
//	:Actor(ownerID),
//	m_attackRange(attackRange)
//{
//	SetAttackDamage(attackDamage);
//}
//
//Unit::~Unit()
//{
//}
//
//boost::property_tree::ptree Unit::Serialize()
//{
//    boost::property_tree::ptree unitXml;
//    unitXml.add("Unit", "");
//    return unitXml;
//}
//
//void Unit::NotifyNewTurn()
//{
//	Player player = GameSession::GetInstance().GetWorldState()->GetPlayer(m_ownerID);
//	// TODO: Update all player ressources
//}